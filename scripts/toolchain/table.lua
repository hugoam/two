-- two toolchain
-- table

null = {}

function table.extend(dest, source)
    for _, v in ipairs(source) do
        table.insert(dest, v)
    end
end

function table.union(dest, source)
    local result = table.copy(dest)
    for _, v in ipairs(source) do
        if not table.contains(dest, v) then
            table.insert(result, v)
        end
    end
    return result
end

function table.inverse(source)
    local result = {}
    for i = #source, 1, -1 do
        table.insert(result, source[i])
    end
    return result
end

function table.copy(source)
    local result = {}
    for _, c in ipairs(source) do
        table.insert(result, c)
    end
    return result
end

function table.traverse(tables, children, callback, visited)
    local queue = tables
    local cache = visited or {}
    while next(queue) ~= nil do
        local n = table.remove(queue, 1)
        callback(n)
        table.insert(cache, n)
        
        for _, c in ipairs(n[children] or {}) do
            if not table.contains(queue, c) and not table.contains(cache, c) then
                table.insert(queue, c)
            end
        end
    end
end

function sort_topological(nodes, children, nowalk)
    local sorted = {}
    local queue = table.copy(nodes)
    
    visit = function(n)
        if n.perm_mark then return end
        if n.temp_mark then return end
        n.temp_mark = true
        
        for _, c in ipairs(n[children] or {}) do
            if not nowalk or table.contains(nodes, c) then
                visit(c)
            end
        end
        
        n.perm_mark = true
        table.insert(sorted, n)
    end
    
    while next(queue) ~= nil do
        local n = table.remove(queue, 1)
        visit(n)
    end

    -- clear the markers for next sort
    for _, n in ipairs(sorted) do
        n.perm_mark = nil
        n.temp_mark = nil
    end
    
    return sorted
end
