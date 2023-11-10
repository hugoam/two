mouseButton = function(event)
{
	if(event.which == 1)
		return Module.MouseButton.LEFT_BUTTON;
	else if(event.which == 2)
		return Module.MouseButton.MIDDLE_BUTTON;
	else if(event.which == 3)
		return Module.MouseButton.RIGHT_BUTTON;
}

HtmlPreloader = function(rootdir)
{
	this.rootdir = rootdir;
	this.files = [];
	this.images = [];
	this.loaded = 0;
	this.preloaded = false;
	
	this.preloadDir = function(dir)
	{
		Module.print(dir);
		var files = FS.readdir(dir);

		for(var i = 0; i < files.length; ++i)
		{
			var path = dir + files[i];
			Module.print(path);

			if(files[i] == '.' || files[i] == '..')
				continue;

			if(FS.isDir(FS.lstat(path).mode))
			{
				this.preloadDir(path + '/');
			}
			else
			{
				var preloader = this;
				var img = new Image();
				var file = path.replace(this.rootdir,'');
				this.images.push(img);
				this.files.push(file);
				img.src = path;
				img.onload = function()
				{
					preloader.loaded++;
					if (preloader.loaded === preloader.images.length)
					{
						Module.print("Finished loading " + preloader.loaded + " images");
						preloader.preloaded = true;
					}
				};
			}
		}
	};
	
	this.preload = function()
	{
		this.preloadDir(this.rootdir);
	}
};

HtmlTarget = Module.InkTarget.extend('InkTarget',
{
	__construct: function(layers, width, height, uiWindow)
	{
		this.__parent.__construct.call(this, layers);
		this.uiWindow = uiWindow;
		this.element = document.createElement('div');
		this.element.id = "main_target";
		document.getElementsByClassName('emscripten_border')[0].appendChild(this.element);

		this.element.style.position = 'relative';
		this.element.style.width = width + 'px';
		this.element.style.height = height + 'px';
		this.element.style.backgroundColor = 'rgb(0,0,0)'; 
		
		var target = this.element;
		this.element.addEventListener('mousedown', function(event) {
			var rect = target.getBoundingClientRect();
			var x = Math.min(event.pageX - rect.left, width);
			var y = Math.min(event.pageY - rect.top, height);
			uiWindow.dispatchMousePressed(x, y, mouseButton(event));
			return false;
		});
		this.element.addEventListener('mouseup', function(event) {
			var rect = target.getBoundingClientRect();
			var x = Math.min(event.pageX - rect.left, width);
			var y = Math.min(event.pageY - rect.top, height);
			uiWindow.dispatchMouseReleased(x, y, mouseButton(event));
			return false;
		});
		this.element.addEventListener('mousemove', function(event) {
			var rect = target.getBoundingClientRect();
			var x = Math.min(event.pageX - rect.left, width);
			var y = Math.min(event.pageY - rect.top, height);
			uiWindow.dispatchMouseMoved(x, y, 0.0, 0.0);
			return false;
		});
		document.getElementById('canvas').style.display = 'none';
	},
});

