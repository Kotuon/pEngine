local maxVelocity = 25.0
local idleRadius = 0.10
local pushForce = 50.0
local dirVariation = 0.5
local pushVariation = 0.2
local physics = object:GetPhysics()
local transform = object:GetTransform()

function Idle()
    if (physics.velocity == zero_vec3())
    then
        physics:ApplyForce(normalize(random_vec3(-100.0, 100.0)), pushForce)
        return
    end

    local distanceFromStart = distance(transform.position, transform.startPosition)
    local combinedRadius = transform.scale.x + idleRadius

    if (distanceFromStart > combinedRadius)
    then
        local direction = normalize(get_direction(transform.startPosition, transform.position))
        direction = add_float(direction, random_float(-dirVariation, dirVariation))
        physics:ApplyForce(direction, pushForce + random_float(-pushVariation, pushVariation))
        return
    end

    if (length(physics.velocity) < maxVelocity)
    then
        local direction = normalize(physics.velocity)
        direction = add_float(direction, random_float(-dirVariation, dirVariation))
        physics:ApplyForce(direction, pushForce + random_float(-pushVariation, pushVariation))
    end
end

function Start()
    --print "Start"
end

function FixedUpdate(delta)
    Idle()
end