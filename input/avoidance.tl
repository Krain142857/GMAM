{`//#\n`}[0];

def kind1@(x, y, tag) = {
    `setPolygonTag(4, 1, 1, 70, random(360), `x`, `y`, objChe, 0, `tag`);
    var t = irandom(4);
    with (objChe) if (tag == `tag`)
        image_index = t;\n`
}

{kind1@(100, 100, 16)}[16];
{kind1@(100, 230, 20)}[20];
{kind1@(100, 370, 24)}[24];
{kind1@(100, 500, 28)}[28];
{kind1@(700, 100, 32)}[32];
{kind1@(700, 230, 36)}[36];
{kind1@(700, 370, 40)}[40];
{kind1@(700, 500, 44)}[44];
{kind1@(300, 304, 48)}[48];
{kind1@(400, 304, 56)}[56];
{kind1@(500, 304, 64)}[64];
{
    `with (objChe)
        speed = 5;\n`
}[72];



{`with (objAAAAMiku) alarm[0] = 1;\n`}[80];
{
    `with (objAAAAMiku) {redEff = 1; blueEff = 0;}
    with (objA1) 
        if (sprite_index == sprRedEffNote) {
            image_index = 1;
            notKiller = true;
        }
        else {
            image_index = 0;
            notKiller = false;
        }
    \n`
}[80:64:272];

{
    `with (objAAAAMiku) {redEff = 0; blueEff = 1;}
    with (objA1) 
        if (sprite_index == sprBlueEffNote){ 
            image_index = 1;
            notKiller = true;
        }
        else {
            image_index = 0;
            notKiller = false;
        }
    \n`
}[112:64:272];



{
    `shootPolygonTag(24, 1, 1, 5, random(360), objAAAAMiku.x, objAAAAMiku.y, objChe, 0, 144);
    with (objChe)
        if (tag == 144)
            image_index = irandom(4);\n`
}[144];

{
    `with (objChe)
        if (tag == 144)
            direction = random(360);\n`
}[152];

{
    `with (objChe)
        if (tag == 144)
            direction = random(360);\n`
}[160];

{
    `with (objChe)
        if (tag == 144) {
            var t = random(360);
            repeat(3) {
                `instance_create@(`x`, `y`, `objChe`, direction = `t`, speed = `random_range(5, 10)`, tag = 164, image = `image_index`)`
                t += 120;
            }
            instance_destroy();
        }\n`
}[164];

{
    `with (objChe)
        if (tag == 164)
            direction += 180;\n`
}[176:4:196];

{
    `with (objAAAAMiku) alarm[1] = 1;`
}[208];


{
    `with (objAAAAMiku) alarm[1] = 0;`
}[272];

{
    `with (objAAAAMiku) alarm[0] = 0;`
}[272];

{
    `
    with (objA1) {
        image_index = 0;
        notKiller = false;
    }
    with (objChe) {
        speed = 0.3;
        aim = true;
        curve = false;
        dirsync = true;
        turning = false;
    }\n`
}[272];

{
    `
    with (objChe) {
        speed = 1;
        aim = false;
        direction = point_direction(x, y, objAAAAMiku.x, objAAAAMiku.y);
    }\n`
}[304];

{
    `
    with (objChe) {
        speed = 8;
        direction += 180;
    }\n`
}[320];

{
    `
    instance_create(100, 128, objAAAAMiku);
    instance_create(700, 112, objAAAAMiku);
    with (objAAAAMiku) alarm[3] = 1;\n`
}[328];

{
    `with (objAAAAMiku)
        instance_destroy();
    instance_create(400, 128, objAAAARed);
    \n`
}[336];


{
    `with (objAAAAMiku) {
        dir = 90;
        alarm[2] = 1;
    }`
}[80];


{
    `with (objAAAAMiku) alarm[2] = 0;`
}[144];

//for object
{
    `/*
    //alarm[0]
    with (objAAAAMiku) {
        `instance_create@(`x`, `y`, `objA2`, speed = `5`)`;
        with (a) path_start(path0, speed, path_action_stop, true);
        a.alarm[0] = 1;
    }
    */\n`
}[0];

{
    `with (objAAAARed)
        alarm[0] = 1;
    \n`
}[336];

{
    `with (objAAAARed)
        alarm[1] = 1;
    \n`
}[464];

{
    `with (objAAAARed) {
        alarm[0] = 0;
        alarm[2] = 1;
    }
    \n`
}[592];

{
    `with (objAAAARed) {
        alarm[3] = 1;
    }
    \n`
}[656];


{
    `with (objAAAARed) {
        alarm[4] = 1;
    }
    \n`
}[848];

{
    `with (objAAAARed) {
        alarm[3] = 0;
        alarm[5] = 1;
    }
    \n`
}[976];

{
    `with (objAAAARed) {
        alarm[6] = 1;
    }
    \n`
}[1040];

{
    `with (objAAAARed) {
        alarm[4] = 0;
        alarm[7] = 1;
    }
    \n`
}[1104];

{
    `with (objAAAARed) {
        alarm[8] = 1;
    }
    \n`
}[1200];

{
    `with (objAAAARed) {
        alarm[1] = 0;
        alarm[2] = 0;
        alarm[5] = 0;
        alarm[6] = 0;
        alarm[7] = 0;
        alarm[8] = 0;
    }
    with (objChe) {
        speed = 0;
    }
    \n`
}[1336];

{
    `if (instance_exists(objPlayer)){
        with (objChe) {
            if (tag == -50) {
                direction = point_direction(objPlayer.x, objPlayer.y, x, y);
                speed = 12;
            } else {
                dirsync = false;
                turning = true;
                ddi = 10;
            }
        }
    }\n`
}[1344];

{
    `with (objChe) {
        tag = choose(-100, -200);
        if (tag == -100) {
            dirsync = true;
            turning = false;
            image_index = note.red;
            direction = point_direction(x, y, objAAAARed.x, objAAAARed.y);
            speed = 2;
        }
    }\n`
}[1360];

{
    `with (objChe) {
        if (tag == -200) {
            dirsync = true;
            turning = false;
            image_index = note.blue;
            direction = point_direction(x, y, objAAAARed.x, objAAAARed.y);
        }
    }\n`
}[1376];

{
    `with (objChe) {
        if (tag == -200) {
            direction = 0;
            speed = 5;
        }
    }\n`
}[1392];

{
    `with (objChe) {
        if (tag == -200) {
            direction = 180;
            speed = 5;
        }
    }\n`
}[1400];

{
    `with (objChe) {
        if (tag == -200) {
            direction = 90;
            speed = 5;
        }
    }\n`
}[1408];

{
    `with (objChe) {
        if (tag == -200) {
            direction = 270;
            speed = 5;
        }
    }\n`
}[1416];

{
    `with (objChe) {
        if (tag == -100) {
            `instance_create@(`x`, `y`, `objA3`, image = `note.yellow`, direction = `direction`)`;
            a.alarm[0] = random(global.SPB * 4);
            instance_destroy();
        }
    }\n`
}[1424];