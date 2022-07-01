def instance_create@(x, y, obj, 
    direction = 0, speed = 0, friction = 0, gravity = 0, gravity_direction = 270, tag = 0,
    sprite = `a.sprite_index`, image = `a.image_index`, image_speed = `a.image_speed`, xscale = 1, yscale = 1) 
    = {
    `repeat(1) {\n`
    `var a = instance_create(`x`, `y`, `obj`);\n`
    direction == 0 ? ``: { `a.direction = ` direction `;\n` }
    speed == 0 ? ``: { `a.speed = ` speed `;\n` }
    friction == 0 ? ``: { `a.friction = ` friction `;\n` }
    gravity == 0 ? ``: { `a.gravity = ` gravity `;\n` }
    gravity_direction == 270 ? ``: { `a.gravity_direction = ` gravity_direction `;\n` }
    tag == 0 ? ``: { `a.tag = ` tag `;\n` }
    sprite == `a.sprite_index` ? `` : { `a.sprite_index = ` sprite `;\n` }
    image == `a.image_index` ? `` : { `a.image_index = ` image `;\n` }
    image_speed == `a.image_speed` ? `` : { `a.image_speed = ` image_speed `;\n` }
    xscale == 1 ? ``: { `a.image_xscale = ` xscale `;\n` }
    yscale == 1 ? ``: { `a.image_xscale = ` yscale `;\n` }
    `}\n`
}