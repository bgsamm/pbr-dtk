#include "version.hpp"

#include "gs/GSmath.hpp"

// TODO name these variables
static GSvec3 lbl_80493608(1f, 0f, 0f);
static GSvec3 lbl_80493614(0f, 1f, 0f);
static GSvec3 lbl_80493620(0f, 0f, 1f);
static GSvec3 lbl_8049362C(0f, 0f, 0f);
static GSvec3 lbl_80493638(1f, 1f, 1f);

static GSvec2 lbl_8063F5B0(0f, 0f);
static GSvec2 lbl_8063F5B8(1f, 1f);

void GSmath::rotateVec3ByQuat(GSvec3 *p, GSquat *r) {
    // TODO get this to match...
    f32 rx = r->x;
    f32 ry = r->y;
    f32 rz = r->z;
    f32 rw = r->w;

    f32 px = p->x;
    f32 py = p->y;
    f32 pz = p->z;

    f32 rx2 = rx * rx;
    f32 ry2 = ry * ry;
    f32 rz2 = rz * rz;
    f32 rw2 = rw * rw;

    f32 rxry = rx * ry;
    f32 rzrw = rz * rw;
    f32 ryrw = ry * rw;
    f32 rxrz = rx * rz;
    f32 ryrz = ry * rz;
    f32 rxrw = rx * rw;

    f32 temp1 = pz * (ryrw + rxrz);
    f32 temp2 = py * (rxry - rzrw);
    f32 temp3 = pz * (ryrz - rxrw);
    f32 temp4 = px * (rxry + rzrw);
    f32 temp5 = py * (ryrz + rxrw);
    f32 temp6 = px * (rxrz - ryrw);

    f32 xtemp1 = px * (rw2 + rx2 - rz2 - ry2);
    f32 xtemp2 = 2f * (temp1 + temp2);

    f32 ytemp1 = py * (ry2 - rz2 + rw2 - rx2);
    f32 ytemp2 = 2f * (temp4 + temp3);

    f32 ztemp1 = pz * (rz2 - ry2 - rx2 + rw2);
    f32 ztemp2 = 2f * (temp5 + temp6);

    p->x = xtemp1 + xtemp2;
    p->y = ytemp1 + ytemp2;
    p->z = ztemp1 + ztemp2;
}
