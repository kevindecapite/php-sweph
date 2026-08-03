/* This is a generated file for PHP 8.4+ compatibility.
 * Stub hash: sweph_php84_strict_v2 */

// ==========================================
// 1. ASTROLOGICAL / CALCULATIONS
// ==========================================

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_calc, 0, 3, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, tjd_et, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, ipl, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, iflag, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_swe_calc_ut arginfo_swe_calc

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_calc_pctr, 0, 4, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, tjd_et, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, ipl, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, iplctr, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, iflag, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_solcross, 0, 3, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, x2cross, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, jd_et, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, iflag, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_swe_solcross_ut arginfo_swe_solcross
#define arginfo_swe_mooncross arginfo_swe_solcross
#define arginfo_swe_mooncross_ut arginfo_swe_solcross

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_fixstar, 0, 3, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, star, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, tjd_et, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, iflag, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_swe_fixstar2 arginfo_swe_fixstar
#define arginfo_swe_fixstar_ut arginfo_swe_fixstar
#define arginfo_swe_fixstar2_ut arginfo_swe_fixstar

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_fixstar_mag, 0, 1, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, star, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_swe_fixstar2_mag arginfo_swe_fixstar_mag


// ==========================================
// 2. SYSTEM / CONFIGURATION (VOID & NULLABLE)
// ==========================================

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_close, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_set_ephe_path, 0, 0, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, path, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_set_jpl_file, 0, 1, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO(0, fname, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_get_planet_name, 0, 1, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, ipl, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_set_topo, 0, 3, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO(0, geolon, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, geolat, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, geoalt, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_version, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()


// ==========================================
// 3. DATE & TIME CONVERSIONS
// ==========================================

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_julday, 0, 4, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, hour, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gregflag, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_revjul, 0, 1, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, jd, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gregflag, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_utc_to_jd, 0, 7, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, hour, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, min, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, dsec, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, gregflag, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_day_of_week, 0, 1, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, jd, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()


// ==========================================
// 4. HOUSES & POSITIONS
// ==========================================

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_houses, 0, 4, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, tjd_ut, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, geolat, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, geolon, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, hsys, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_houses_ex, 0, 5, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, tjd_ut, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, iflag, IS_LONG, 0)
    ZEND_ARG_TYPE_INFO(0, geolat, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, geolon, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, hsys, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_swe_houses_ex2 arginfo_swe_houses_ex

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_house_name, 0, 1, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, hsys, IS_STRING, 0)
ZEND_END_ARG_INFO()


// ==========================================
// 5. HELIOPOLY & OTHER MATH UTILS
// ==========================================

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_degnorm, 0, 1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, deg, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_radnorm, 0, 1, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, rad, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_swe_split_deg, 0, 2, IS_ARRAY, 0)
    ZEND_ARG_TYPE_INFO(0, ddeg, IS_DOUBLE, 0)
    ZEND_ARG_TYPE_INFO(0, roundflag, IS_LONG, 0)
ZEND_END_ARG_INFO()


// ==========================================
// 6. FUNCTION DECLARATIONS & ENTRY TABLE
// ==========================================

ZEND_FUNCTION(swe_calc);
ZEND_FUNCTION(swe_calc_ut);
ZEND_FUNCTION(swe_calc_pctr);
ZEND_FUNCTION(swe_solcross);
ZEND_FUNCTION(swe_solcross_ut);
ZEND_FUNCTION(swe_mooncross);
ZEND_FUNCTION(swe_mooncross_ut);
ZEND_FUNCTION(swe_fixstar);
ZEND_FUNCTION(swe_fixstar2);
ZEND_FUNCTION(swe_fixstar_ut);
ZEND_FUNCTION(swe_fixstar2_ut);
ZEND_FUNCTION(swe_fixstar_mag);
ZEND_FUNCTION(swe_fixstar2_mag);
ZEND_FUNCTION(swe_close);
ZEND_FUNCTION(swe_set_ephe_path);
ZEND_FUNCTION(swe_set_jpl_file);
ZEND_FUNCTION(swe_get_planet_name);
ZEND_FUNCTION(swe_set_topo);
ZEND_FUNCTION(swe_version);
ZEND_FUNCTION(swe_julday);
ZEND_FUNCTION(swe_revjul);
ZEND_FUNCTION(swe_utc_to_jd);
ZEND_FUNCTION(swe_houses);
ZEND_FUNCTION(swe_houses_ex);
ZEND_FUNCTION(swe_houses_ex2);
ZEND_FUNCTION(swe_house_name);
ZEND_FUNCTION(swe_degnorm);
ZEND_FUNCTION(swe_radnorm);
ZEND_FUNCTION(swe_split_deg);
ZEND_FUNCTION(swe_day_of_week);

static const zend_function_entry ext_functions[] = {
    ZEND_FE(swe_calc, arginfo_swe_calc)
    ZEND_FE(swe_calc_ut, arginfo_swe_calc_ut)
    ZEND_FE(swe_calc_pctr, arginfo_swe_calc_pctr)
    ZEND_FE(swe_solcross, arginfo_swe_solcross)
    ZEND_FE(swe_solcross_ut, arginfo_swe_solcross_ut)
    ZEND_FE(swe_mooncross, arginfo_swe_mooncross)
    ZEND_FE(swe_mooncross_ut, arginfo_swe_mooncross_ut)
    ZEND_FE(swe_fixstar, arginfo_swe_fixstar)
    ZEND_FE(swe_fixstar2, arginfo_swe_fixstar2)
    ZEND_FE(swe_fixstar_ut, arginfo_swe_fixstar_ut)
    ZEND_FE(swe_fixstar2_ut, arginfo_swe_fixstar2_ut)
    ZEND_FE(swe_fixstar_mag, arginfo_swe_fixstar_mag)
    ZEND_FE(swe_fixstar2_mag, arginfo_swe_fixstar2_mag)
    ZEND_FE(swe_close, arginfo_swe_close)
    ZEND_FE(swe_set_ephe_path, arginfo_swe_set_ephe_path)
    ZEND_FE(swe_set_jpl_file, arginfo_swe_set_jpl_file)
    ZEND_FE(swe_get_planet_name, arginfo_swe_get_planet_name)
    ZEND_FE(swe_set_topo, arginfo_swe_set_topo)
    ZEND_FE(swe_version, arginfo_swe_version)
    ZEND_FE(swe_julday, arginfo_swe_julday)
    ZEND_FE(swe_revjul, arginfo_swe_revjul)
    ZEND_FE(swe_utc_to_jd, arginfo_swe_utc_to_jd)
    ZEND_FE(swe_houses, arginfo_swe_houses)
    ZEND_FE(swe_houses_ex, arginfo_swe_houses_ex)
    ZEND_FE(swe_houses_ex2, arginfo_swe_houses_ex2)
    ZEND_FE(swe_house_name, arginfo_swe_house_name)
    ZEND_FE(swe_degnorm, arginfo_swe_degnorm)
    ZEND_FE(swe_radnorm, arginfo_swe_radnorm)
    ZEND_FE(swe_split_deg, arginfo_swe_split_deg)
    ZEND_FE(swe_day_of_week, arginfo_swe_day_of_week)
    ZEND_FE_END
};