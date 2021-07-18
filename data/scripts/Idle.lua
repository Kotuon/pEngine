local maxVelocity = 25.0
local idleRadius = 0.10
local pushForce = 50.0
local dirVariation = 0.5
local pushVariation = 0.0

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
        print "Go home"
        physics:ApplyForce(normalize(get_direction(transform.startPosition, transform.position)), pushForce)
        return
    end

    if (length(physics.velocity) < maxVelocity)
    then
        physics:ApplyForce(normalize(physics.velocity), pushForce)
    end
end

function Start()
    print "Start"
end

function FixedUpdate(delta)
    Idle()
end