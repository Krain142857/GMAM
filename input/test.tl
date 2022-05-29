def cen_x = 400
def cen_y = 304
{`
//
var a = instance_create(`cen_x`, `cen_y`, objA1);
with(a) 
{
    image_xscale = 20;
    image_yscale = 20;
    alarm[0] = 1;
    motion_set(90, 2);
}
`}[6];


[5, cen_y: 10: cen_x]{`
//
var a = instance_create(`cen_x`, `cen_y`, objA1);
with(a) 
{
    image_xscale = 20;
    image_yscale = 20;
    alarm[0] = 1;
    motion_set(90, 2);
}
`};