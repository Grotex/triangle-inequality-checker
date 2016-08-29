#include "triangle.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <cfloat>

Triangle::Triangle(long_d _a, long_d _b, long_d _c)
{
    a = _a; b = _b; c = _c;
    init_angles();
    init_Rrs();
}
    
void Triangle::init_angles()
{
    cosA = (b * b + c * c - a * a) / (2 * b * c);
    cosB = (c * c + a * a - b * b) / (2 * c * a);
    cosC = (a * a + b * b - c * c) / (2 * a * b);
        
    A = acos(cosA) * 180 / M_PI;
    B = acos(cosB) * 180 / M_PI;
    C = acos(cosC) * 180 / M_PI;
}
    
void Triangle::init_Rrs()
{
    s = (a + b + c) / 2;
    S = sqrt(s * (s - a) * (s - b) * (s - c));
    r = S / s;
    R = (a * b * c) / (4 * S);
}

long_d Triangle::get_max_angle()
{
    return max(A, max(B, C));
}

long_d Triangle::get_min_angle()
{
    return min(A, min(B, C));
}

bool Triangle::is_bager_type_I()
{
    // Check if angles satisfy a relation of the form: A >= B >= 60 >= C.
    // If false, then we are sure that triangle is Bager Type II.
    long_d LHS = s;
    long_d RHS = sqrt(3) * (R + r);
    return (LHS > RHS || almost_equal_relative(LHS, RHS));
}

void Triangle::init_sinA_sinB_sinC()
{
    long_d twice_R = 2 * R;
    sinA = a / twice_R;
    sinB = b / twice_R;
    sinC = c / twice_R;
}

void Triangle::init_sin2A_sin2B_sin2C()
{
    auto sin2A_sin2B_sin2C = get_trig_func_of_nA_nB_nC(&sin, 2);
    sin2A = get<0>(sin2A_sin2B_sin2C);
    sin2B = get<1>(sin2A_sin2B_sin2C);
    sin2C = get<2>(sin2A_sin2B_sin2C);
}

void Triangle::init_cosA_cosB_cosC()
{
    // Already initialized when calling constructor.
}

void Triangle::init_tanA_tanB_tanC()
{
    auto tanA_tanB_tanC = get_trig_func_of_nA_nB_nC(&tan, 1);
    tanA = get<0>(tanA_tanB_tanC);
    tanB = get<1>(tanA_tanB_tanC);
    tanC = get<2>(tanA_tanB_tanC);
}

void Triangle::init_sinA2_sinB2_sinC2()
{
    auto sinA2_sinB2_sinC2 = get_trig_func_of_nA_nB_nC(&sin, 0.5);
    sinA2 = get<0>(sinA2_sinB2_sinC2);
    sinB2 = get<1>(sinA2_sinB2_sinC2);
    sinC2 = get<2>(sinA2_sinB2_sinC2);
}

void Triangle::init_cosA2_cosB2_cosC2()
{
    auto cosA2_cosB2_cosC2 = get_trig_func_of_nA_nB_nC(&cos, 0.5);
    cosA2 = get<0>(cosA2_cosB2_cosC2);
    cosB2 = get<1>(cosA2_cosB2_cosC2);
    cosC2 = get<2>(cosA2_cosB2_cosC2);
}

void Triangle::init_tanA2_tanB2_tanC2()
{
    auto tanA2_tanB2_tanC2 = get_trig_func_of_nA_nB_nC(&tan, 0.5);
    tanA2 = get<0>(tanA2_tanB2_tanC2);
    tanB2 = get<1>(tanA2_tanB2_tanC2);
    tanC2 = get<2>(tanA2_tanB2_tanC2);
}

tuple_3 Triangle::get_trig_func_of_nA_nB_nC(trig_func func, long_d n)
{
    long_d angle_ct = n * M_PI / 180;
    long_d func_nA = func(A * angle_ct);
    long_d func_nB = func(B * angle_ct);
    long_d func_nC = func(C * angle_ct);
    
    return tuple<long_d ,long_d, long_d>(func_nA, func_nB, func_nC);
}

void Triangle::init_K()
{
    init_sinA2_sinB2_sinC2();
    K = sinA2 + sinB2 + sinC2;
}

void Triangle::init_Q()
{
    init_cosA2_cosB2_cosC2();
    Q = cosA2 + cosB2 + cosC2;
}

void Triangle::init_ha_hb_hc()
{
    long_d twice_area = 2 * S;
    ha = twice_area / a;
    hb = twice_area / b;
    hc = twice_area / c;
}

void Triangle::init_la_lb_lc()
{
    init_cosA2_cosB2_cosC2();
    la = 2 * b * c * cosA2 / (b + c);
    lb = 2 * c * a * cosB2 / (c + a);
    lc = 2 * a * b * cosC2 / (a + b);
}

void Triangle::init_ma_mb_mc()
{
    ma = 0.5 * sqrt(2 * (b * b + c * c) - a * a);
    mb = 0.5 * sqrt(2 * (c * c + a * a) - b * b);
    mc = 0.5 * sqrt(2 * (a * a + b * b) - c * c);
}

void Triangle::init_sa_sb_sc()
{
    init_ma_mb_mc();
    sa = 2 * b * c * ma / (b * b + c * c);
    sb = 2 * c * a * mb / (c * c + a * a);
    sc = 2 * a * b * mc / (a * a + b * b);
}

void Triangle::init_ra_rb_rc()
{
    ra = S / (s - a);
    rb = S / (s - b);
    rc = S / (s - c);
}

void Triangle::init_HA_HB_HC()
{
    HA = 2 * R * abs(cosA);
    HB = 2 * R * abs(cosB);
    HC = 2 * R * abs(cosC);
}

void Triangle::init_IA_IB_IC()
{
    init_sinA2_sinB2_sinC2();
    IA = r / sinA2;
    IB = r / sinB2;
    IC = r / sinC2;
}

void Triangle::init_GA_GB_GC()
{
    init_ma_mb_mc();
    GA = (2.0 * ma) / ((long_d) 3);
    GB = (2.0 * mb) / ((long_d) 3);
    GC = (2.0 * mc) / ((long_d) 3);
}
