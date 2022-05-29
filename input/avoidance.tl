def cen_x = 400
def cen_y = 304
def instance_create(x, y, obj, xscale = 1, yscale = 1) = 
{`
    var a = instance_create(`x`, `y`, `obj`);
    a.image_xscale = `xscale`;
    a.image_yscale = `yscale`;
`}

{instance_create(400 607 `objA1` yscale = 20 xscale = 10)}[0, 5:5:20++, 100];


[2]{instance_create(cen_x, 607, `objA1`)};