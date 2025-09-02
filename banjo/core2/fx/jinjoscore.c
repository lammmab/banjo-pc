#include <ultra64.h>
#include "core1/core1.h"
#include "functions.h"
#include "variables.h"


extern f32 func_802FB0E4(struct8s *);

/* .data */
u16 D_8036A070[0xD][0x10] = {
    {0x0000, 0xF33D, 0x1085, 0xB167, 0xF439, 0x9963, 0xF233, 0x6117, 0xDA6F, 0xF2B7, 0xDC33, 0xFD3D, 0x38CF, 0xC9EB, 0x819F, 0xD32D},
    {0x0000, 0xF2FD, 0x30CD, 0xC9EB, 0xF4BB, 0xA1A5, 0x8261, 0xF277, 0xDB31, 0xDCB3, 0xA267, 0x6319, 0xF379, 0xF231, 0xC26F, 0xDA2D},
    {0x0000, 0xF2FB, 0x0847, 0xA163, 0xCB2F, 0x521F, 0xF479, 0xFFFF, 0xD1ED, 0x5115, 0xADEF, 0x7BA1, 0x3AA1, 0xF273, 0x6BF1, 0xD433},
    {0x0000, 0xE22F, 0xB9A7, 0x108B, 0xF47B, 0xACEB, 0x4A61, 0xC739, 0xF2B9, 0x891F, 0x0263, 0x84AB, 0xCC31, 0xB2EB, 0x314D, 0x0915},
    {0x0000, 0xDA2F, 0xB1A5, 0x088D, 0xD3F3, 0x8C65, 0xCF39, 0x1A63, 0x80DD, 0xF2B9, 0x5257, 0xFCBB, 0x38D7, 0xA5B5, 0x6BA9, 0xF273},
    {0x0000, 0xE22F, 0xB1A7, 0x08CF, 0xE3B5, 0xBC6F, 0x6A61, 0xC6B7, 0xF2B9, 0x88DD, 0x09DF, 0x3AA7, 0x8C67, 0xF4BB, 0x5295, 0x40D5},
    {0x0000, 0xE22F, 0xC1E9, 0x088D, 0xD3B1, 0xBDF1, 0x8C27, 0xF2B9, 0x9161, 0xF4B9, 0x6DB7, 0x099D, 0x4151, 0x436D, 0x6A23, 0x739D},
    {0x0000, 0xF2B9, 0x5259, 0xAA29, 0x108D, 0xF439, 0x7BA5, 0xBDF1, 0xEA2F, 0x33AF, 0x9121, 0x963B, 0x119B, 0xCBEF, 0xBAF1, 0xD1EB},
    {0x0000, 0xF275, 0x0849, 0xA165, 0xF479, 0x521B, 0xA52F, 0xCEF9, 0x19E1, 0xD9ED, 0x4BED, 0xC32F, 0x73A3, 0x2951, 0xF2FB, 0xDBF3},
    {0x0000, 0xEA33, 0xA1A5, 0x1917, 0xB56D, 0x429D, 0xF2FB, 0xECB9, 0x0847, 0xCB6F, 0x22B1, 0x6159, 0x7CAD, 0xD1ED, 0x39D1, 0x73A3},
    {0x0000, 0xF2FB, 0xB1A5, 0x4995, 0xCBAF, 0x9CE7, 0x1049, 0xD9EF, 0xC5F3, 0x095B, 0xF439, 0xA337, 0x4AE1, 0xA2E9, 0xF273, 0x64AD},
    {0x0000, 0xF2B9, 0x6159, 0xC9EB, 0xCB2F, 0xF47B, 0xA9A5, 0xF273, 0x92E5, 0x20C9, 0xDBF1, 0xF2FD, 0x39CF, 0xE22F, 0x9961, 0xBAEB},
    {0x0000, 0xF2BB, 0xC9EB, 0x6959, 0xC32D, 0xEA31, 0x314D, 0xF3FB, 0x5AD7, 0xA965, 0xF53B, 0xF277, 0x911F, 0xD431, 0xE2F3, 0xFB3F}
};

enum asset_e D_8036A210[5] = {0x7DF, 0x7DF, 0x7DF, 0x7DF, 0x7DF};

Gfx D_8036A228[] =
{
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

/* .bss */
u16 D_80381620[0xD][5][0x10];
BKSprite *D_80381E40[5];
f32   D_80381E54;
u8    D_80381E58[5];
f32   D_80381E60[5];
f32   D_80381E78[5];
struct7s D_80381E90;


/* .code */
struct7s *fxjinjoscore_new(enum item_e arg0){
    s32 i;
    s32 red;
    s32 green;
    s32 blue;
    s32 alpha;
    s32 tmp_green;
    s32 tmp_alpha;
    s32 j;
    u16 rgba;
    u32 jinjo_id;

    D_80381E54 = 1.0f;
    for (jinjo_id = 0; jinjo_id < 5; jinjo_id++)
    {
        D_80381E60[jinjo_id] = 0.0f;
        D_80381E58[jinjo_id] = (item_getCount(ITEM_12_JINJOS) & (1 << jinjo_id)) ? (3) : (0);
        for (i = 0; i < 0xD; i++)
        {
            for (j = 0; j < 0x10; j++)
            {
                rgba = D_8036A070[i][j];
                tmp_alpha = (rgba >> 0) & 0x1;

                red = (rgba >> 0xB) & 0x1F;
                tmp_green = green = ((rgba >> 6) & 0x1F);
                blue = (rgba >> 1) & 0x1F;
                alpha = tmp_alpha;
                if (((red < 0x10) || (green < 0x10)) || (blue < 0x10))
                {
                    switch (jinjo_id)
                    {

                    case 0:
                        red = red * 0.25;
                        green = tmp_green * 1.5;
                        break;

                    case 1:
                        red = red * 0.2;
                        green = blue;
                        blue = blue * 0.2;
                        break;

                    case 2:
                        green = blue;
                        blue = tmp_green * 0.4;
                        green *= 0.6;
                        break;

                    case 3:
                        green = green;
                        blue = blue;
                        break;

                    case 4:
                        green = blue;
                        blue = tmp_green * 0.4;
                        alpha = tmp_alpha;
                        break;

                    }

                }
                D_80381620[i][jinjo_id][j] = (((red << 0xB) | (green << 6)) | (blue << 1)) | alpha;
            }

        }
    }
    return &D_80381E90;
}

void fxjinjoscore_free(enum item_e item_id, struct8s * arg1){
    s32 i;

    for(i = 0; i < 5; i++){
        if(D_80381E40[i] != NULL){
            assetCache_free(D_80381E40[i]);
            D_80381E40[i] = NULL;
        }
    }

}

//fxjinjoscore_draw
void fxjinjoscore_draw(s32 arg0, struct8s *arg1, Gfx **gfx, Mtx **mtx, Vtx **vtx) {
    BKSprite *sprite; // s1
    s32 draw_index; // s5
    s32 texture_width; // sp11C
    s32 texture_height; // sp118
    s32 jinjo_id; // sp114
    f32 center_y; // f14 (sp110)
    f32 center_x; // f20 (sp10C)
    f32 x_offset; // f26 (sp108)
    f32 y_offset; // f28 (sp104)
    f32 pos_x; // f30 (sp100)
    s32 i; // v1 (spFC)
    s32 j; // v0_2 (spF8)

    gSPDisplayList((*gfx)++, D_8036A228);
    viewport_setRenderViewportAndOrthoMatrix(gfx, mtx);
    pos_x = 44.0f;
    // Draw all jinjo heads
    for(jinjo_id = 0; jinjo_id < 5; jinjo_id++){
        s32 jinjo_collected; // spF0 <----
        sprite = D_80381E40[jinjo_id];
        jinjo_collected = (D_80381E58[jinjo_id] != 0) ? 1 : 0;
        if (sprite != NULL) {
            func_80347FC0(gfx, sprite, (s32) D_80381E60[jinjo_id], 0, 0, 0, 0, 2, 2, &texture_width, &texture_height);
            // Load the palette for the corresponding jinjo color
            gDPLoadTLUT_pal16((*gfx)++, 0, D_80381620[(s32)D_80381E60[jinjo_id]][jinjo_id]);
            x_offset = 0.0f;
            y_offset = 0.0f;
            // Draw the jinjo head, once if uncollected and twice if collected
            // If the head is drawn twice then the first draw will be the drop shadow
            for (draw_index = jinjo_collected; draw_index >= 0; draw_index--){
                gDPPipeSync((*gfx)++);
                // Draw 0 is the jinjo's head, anything else is a shadow
                if (draw_index != 0) {
                    // Use only primitive color as the color input in order to make a solid color shadow
                    gDPSetCombineLERP((*gfx)++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
                    // Set up a translucent black for primitive color to draw the shadow
                    gDPSetPrimColor((*gfx)++, 0, 0, 0x00, 0x00, 0x00, 0x8C);
                } else {
                    // Use the texture as the color input
                    gDPSetCombineLERP((*gfx)++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
                    // If the jinjo is collected then it's drawn fully opaque, otherwise it's drawn with partial alpha
                    gDPSetPrimColor((*gfx)++, 0, 0, 0x00, 0x00, 0x00, jinjo_collected ? 0xFF : 0x6E);
                }
                center_x = pos_x - (f32) gFramebufferWidth / 2 + x_offset;
                center_y = (f32) gFramebufferHeight / 2 + func_802FB0E4(arg1) - 266.0f + 40.0f + y_offset - D_80381E78[jinjo_id];
                gSPVertex((*gfx)++, *vtx, 4, 0);
                // Set up the positions of the four vertices
                for(i = 0; i < 2; i++){
                    for(j = 0; j  < 2; j++){
                        (*vtx)->v.ob[0] = ((texture_width  * D_80381E54 * j) - (texture_width  * D_80381E54 / 2) + center_x) * 4;
                        (*vtx)->v.ob[1] = ((texture_height * D_80381E54 / 2) - (texture_height * D_80381E54 * i) + center_y) * 4;
                        (*vtx)->v.ob[2] = -20;
                        (*vtx)->v.tc[0] = ((texture_width  - 1) * j) << 6;
                        (*vtx)->v.tc[1] = ((texture_height - 1) * i) << 6;
                        (*vtx)++;
                    }
                }
                // Draw a quad made of the four vertices
                gSP1Quadrangle((*gfx)++, 0, 1, 3, 2, 0);
                x_offset += -2;
                y_offset += 2;
            }
        }
        // Move the next jinjo head over by 32 pixels
        pos_x += 32.0f;
    }
    gDPPipeSync((*gfx)++);
    gDPSetTextureLUT((*gfx)++, G_TT_NONE);
    gDPPipelineMode((*gfx)++, G_PM_NPRIMITIVE);
    viewport_setRenderViewportAndPerspectiveMatrix(gfx, mtx);
}

bool func_802FFA10(f32 arg0, s32 arg1, s32 arg2){
    if(arg1 == 0){
        return TRUE;
    }

    return (D_80381E78[arg1 - 1] < arg0);
}

void fxjinjoscore_update(enum item_e item_id, struct8s *arg1) {
    f32 var_f24;
    s32 temp_s3;
    s32 jinjo_id;
    s32 sp78;

    var_f24 = time_getDelta();
    temp_s3 = func_802FB0D4(arg1);
    sp78 = item_getCount(item_id);
    switch(temp_s3){
        case 1:
            for(jinjo_id = 0; jinjo_id < 5; jinjo_id++){
                if (D_80381E40[jinjo_id] == NULL) {
                    D_80381E40[jinjo_id] = assetcache_get(D_8036A210[jinjo_id]);
                    D_80381E78[jinjo_id] = 64.0f;
                }
            }
            break;

        case 0:
            fxjinjoscore_free(item_id, arg1);
            break;
        
        default:
            break;
    }

    if (temp_s3 != 0) {
        for(jinjo_id = 0; jinjo_id < 5; jinjo_id++){
            switch (D_80381E58[jinjo_id]) {
                case 0:
                    if (((1 << jinjo_id) & sp78) && (temp_s3 == 2) && (D_80381E78[jinjo_id] < 1.0f)) {
                        D_80381E58[jinjo_id] = 2;
                        func_8030E560(SFX_3EE, 26000);
                    }
                    break;
                case 2:
                    D_80381E60[jinjo_id] += var_f24 * 15.0;
                    if ((s32) D_80381E60[jinjo_id] >= 9) {
                        D_80381E60[jinjo_id] = 9.0f;
                        D_80381E58[jinjo_id] = 3;
                    }
                    break;
                case 1:
                    if (0.95 < randf2(0.0f, 1.0f)) {
                        D_80381E58[jinjo_id] = 4;
                    }
                    break;
                case 4:
                    D_80381E60[jinjo_id] += var_f24 * 30.0;
                    if ((s32) D_80381E60[jinjo_id] >= 12) {
                        D_80381E58[jinjo_id] = 3;
                        D_80381E60[jinjo_id] = 12.0f;
                    }
                    break;
                case 3:
                    D_80381E60[jinjo_id] -= var_f24 * 30.0;
                    if ((s32) D_80381E60[jinjo_id] < 10) {
                        D_80381E60[jinjo_id] = 9.0f;
                        D_80381E58[jinjo_id] = 1;
                    }
                    break;
            }

            switch (temp_s3) {                      /* switch 1; irregular */
                case 3:                                 /* switch 1 */
                    break;
                case 1:                                 /* switch 1 */
                case 2:                                 /* switch 1 */
                    if (func_802FFA10(15.0f, jinjo_id, 5)) {
                        if (D_80381E78[jinjo_id] >= 1.0f) {
                            D_80381E78[jinjo_id] *= 0.6;
                        }
                    }
                    break;
            }
        }
    }
}

