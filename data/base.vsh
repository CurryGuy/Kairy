.alias myconst c32 as (0.0, 1.0, -1.0, 0.5)

.alias outpos o0 as position
.alias outtex o1 as texcoord0
.alias outcol o2 as color

.alias inpos v0
.alias intex v1
.alias incol v2

.alias projection c0
.alias modelview c4

main:
    mov r0.xy, inpos.xy
    mov r0.z, myconst.w
    mov r0.w, myconst.y

    dp4 r1.x, modelview[0], r0
    dp4 r1.y, modelview[1], r0
    dp4 r1.z, modelview[2], r0
    dp4 r1.w, modelview[3], r0

    dp4 outpos.x, projection[0], r1
    dp4 outpos.y, projection[1], r1
    dp4 outpos.z, projection[2], r1
    dp4 outpos.w, projection[3], r1

    mov outcol, incol
    mov outtex, intex

    nop
    end
