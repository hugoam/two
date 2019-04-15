// Bindings utilities
function WrapperObject() {
}
WrapperObject.prototype = Object.create(WrapperObject.prototype);
WrapperObject.prototype.constructor = WrapperObject;
WrapperObject.prototype.__class = WrapperObject;
WrapperObject.__cache = {};
Module[WrapperObject] = WrapperObject;
function getCache(cls) {
  return (cls || WrapperObject).__cache;
}
Module['getCache'] = getCache;
function wrapPointer(ptr, cls) {
  var cache = getCache(cls);
  var ret = cache[ptr];
  if (ret) return ret;
  ret = Object.create((cls || WrapperObject).prototype);
  ret.__ptr = ptr;
  return cache[ptr] = ret;
}
Module['wrapPointer'] = wrapPointer;
Module['NULL'] = wrapPointer(0);
function destroy(obj) {
  if (!obj['__destroy']) throw 'Error: Cannot destroy object. (Did you create it yourself?)';
  obj['__destroy']();
  // Remove from cache, so the object can be GC'd and refs added onto it released
  delete getCache(obj.__class)[obj.__ptr];
}
Module['destroy'] = destroy;
function compare(obj1, obj2) {
  return obj1.__ptr === obj2.__ptr;
}
Module['compare'] = compare;
function checkClass(obj, destcls, cls) {
  cls = cls || obj.__class;
  if (cls == destcls) return true;
  else if (cls.__base) return checkClass(obj, destcls, cls.__base);
  else return false;
}
Module['checkClass'] = checkClass;
// Converts big (string or array) values into a C-style storage, in temporary space
var ensureCache = {
  buffer: 0,  // the main buffer of temporary storage
  size: 0,   // the size of buffer
  pos: 0,    // the next free offset in buffer
  temps: [], // extra allocations
  needed: 0, // the total size we need next time
  prepare: function() {
    if (ensureCache.needed) {
      // clear the temps
      for (var i = 0; i < ensureCache.temps.length; i++) {
        Module['_free'](ensureCache.temps[i]);
      }
      ensureCache.temps.length = 0;
      // prepare to allocate a bigger buffer
      Module['_free'](ensureCache.buffer);
      ensureCache.buffer = 0;
      ensureCache.size += ensureCache.needed;
      // clean up
      ensureCache.needed = 0;
    }
    if (!ensureCache.buffer) { // happens first time, or when we need to grow
      ensureCache.size += 128; // heuristic, avoid many small grow events
      ensureCache.buffer = Module['_malloc'](ensureCache.size);
      assert(ensureCache.buffer);
    }
    ensureCache.pos = 0;
  },
  alloc: function(array, view) {
    assert(ensureCache.buffer);
    var bytes = view.BYTES_PER_ELEMENT;
    var len = array.length * bytes;
    len = (len + 7) & -8; // keep things aligned to 8 byte boundaries
    var ret;
    if (ensureCache.pos + len >= ensureCache.size) {
      // we failed to allocate in the buffer, ensureCache time around :(
      assert(len > 0); // null terminator, at least
      ensureCache.needed += len;
      ret = Module['_malloc'](len);
      ensureCache.temps.push(ret);
    } else {
      // we can allocate in the buffer
      ret = ensureCache.buffer + ensureCache.pos;
      ensureCache.pos += len;
    }
    return ret;
  },
  copy: function(array, view, offset) {
    var offsetShifted = offset;
    var bytes = view.BYTES_PER_ELEMENT;
    switch (bytes) {
      case 2: offsetShifted >>= 1; break;
      case 4: offsetShifted >>= 2; break;
      case 8: offsetShifted >>= 3; break;
    }
    for (var i = 0; i < array.length; i++) {
      view[offsetShifted + i] = array[i];
    }
  },
};
function ensureString(value) {
    if (typeof value === 'string') {
        var intArray = intArrayFromString(value);
        var offset = ensureCache.alloc(intArray, HEAP8);
        ensureCache.copy(intArray, HEAP8, offset);
        return offset;
    }
    return value;
}
function ensureRef(value) {
    if (typeof value !== 'undefined' && value !== null) { return value.__ptr; }
	else { return 0; }
}
function ensureRefType(value) {
    if (typeof value !== 'undefined' && value !== null) { return value.__type; }
	else { return 0; }
}
function ensureInt8(value) {
    if (typeof value === 'object') {
        var offset = ensureCache.alloc(value, HEAP8);
        ensureCache.copy(value, HEAP8, offset);
        return offset;
    }
    return value;
}
function ensureInt16(value) {
    if (typeof value === 'object') {
        var offset = ensureCache.alloc(value, HEAP16);
        ensureCache.copy(value, HEAP16, offset);
        return offset;
    }
    return value;
}
function ensureInt32(value) {
    if (typeof value === 'object') {
        var offset = ensureCache.alloc(value, HEAP32);
        ensureCache.copy(value, HEAP32, offset);
        return offset;
    }
    return value;
}
function ensureFloat32(value) {
    if (typeof value === 'object') {
        var offset = ensureCache.alloc(value, HEAPF32);
        ensureCache.copy(value, HEAPF32, offset);
        return offset;
    }
    return value;
}
function ensureFloat64(value) {
    if (typeof value === 'object') {
        var offset = ensureCache.alloc(value, HEAPF64);
        ensureCache.copy(value, HEAPF64, offset);
        return offset;
    }
    return value;
}