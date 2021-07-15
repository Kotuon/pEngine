
function Update(delta)
    io.write(string.format("Hello, Update from %f\n", delta))
end

function FixedUpdate(delta)
    io.write(string.format("Hello, Fixed from %f\n", delta))
end