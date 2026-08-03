/*
  +----------------------------------------------------------------------+
  | PHP Version 8.4+ Swiss Ephemeris extension                           |
  +----------------------------------------------------------------------+
  | Copyright (c) 2007-2026                                              |
  +----------------------------------------------------------------------+
  | Author: Joel Chen (cyjoelchen@gmail.com)                             |
  | Contributor: Alois Treindl, drt04-dev                                |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_swephp.h"

#include "swephexp.h"

#define SWEPH_EXTENSION_VERSION "2.0.0-php84"

// Inkludiere den durch gen_stub.php generierten PHP 8.4 Arginfo-Header
#include "swephp_arginfo.h"

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(swephp)
{
    /* values for gregflag in swe_julday() and swe_revjul() */
    REGISTER_LONG_CONSTANT("SE_JUL_CAL", SE_JUL_CAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_GREG_CAL", SE_GREG_CAL, CONST_CS | CONST_PERSISTENT);

    /* planet numbers for the ipl parameter in swe_calc() */
    REGISTER_LONG_CONSTANT("SE_ECL_NUT", SE_ECL_NUT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SUN", SE_SUN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MOON", SE_MOON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MERCURY", SE_MERCURY, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_VENUS", SE_VENUS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MARS", SE_MARS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_JUPITER", SE_JUPITER, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SATURN", SE_SATURN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_URANUS", SE_URANUS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NEPTUNE", SE_NEPTUNE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_PLUTO", SE_PLUTO, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MEAN_NODE", SE_MEAN_NODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_TRUE_NODE", SE_TRUE_NODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MEAN_APOG", SE_MEAN_APOG, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_OSCU_APOG", SE_OSCU_APOG, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_EARTH", SE_EARTH, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_CHIRON", SE_CHIRON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_PHOLUS", SE_PHOLUS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_CERES", SE_CERES, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_PALLAS", SE_PALLAS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_JUNO", SE_JUNO, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_VESTA", SE_VESTA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_INTP_APOG", SE_INTP_APOG, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_INTP_PERG", SE_INTP_PERG, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SE_NPLANETS", SE_NPLANETS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_AST_OFFSET", SE_AST_OFFSET, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_VARUNA", SE_VARUNA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_FICT_OFFSET", SE_FICT_OFFSET, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_FICT_OFFSET_1", SE_FICT_OFFSET_1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_FICT_MAX", SE_FICT_MAX, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NFICT_ELEM", SE_NFICT_ELEM, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SE_COMET_OFFSET", SE_COMET_OFFSET, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NALL_NAT_POINTS", SE_NALL_NAT_POINTS, CONST_CS | CONST_PERSISTENT);

    /* Hamburger or Uranian "planets" */
    REGISTER_LONG_CONSTANT("SE_CUPIDO", SE_CUPIDO, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HADES", SE_HADES, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ZEUS", SE_ZEUS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_KRONOS", SE_KRONOS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_APOLLON", SE_APOLLON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ADMETOS", SE_ADMETOS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_VULKANUS", SE_VULKANUS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_POSEIDON", SE_POSEIDON, CONST_CS | CONST_PERSISTENT);

    /* other fictitious bodies */
    REGISTER_LONG_CONSTANT("SE_ISIS", SE_ISIS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NIBIRU", SE_NIBIRU, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HARRINGTON", SE_HARRINGTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NEPTUNE_LEVERRIER", SE_NEPTUNE_LEVERRIER, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NEPTUNE_ADAMS", SE_NEPTUNE_ADAMS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_PLUTO_LOWELL", SE_PLUTO_LOWELL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_PLUTO_PICKERING", SE_PLUTO_PICKERING, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_VULCAN", SE_VULCAN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_WHITE_MOON", SE_WHITE_MOON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_PROSERPINA", SE_PROSERPINA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_WALDEMATH", SE_WALDEMATH, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SE_FIXSTAR", SE_FIXSTAR, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SE_ASC", SE_ASC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MC", SE_MC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ARMC", SE_ARMC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_VERTEX", SE_VERTEX, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_EQUASC", SE_EQUASC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_COASC1", SE_COASC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_COASC2", SE_COASC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_POLASC", SE_POLASC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NASCMC", SE_NASCMC, CONST_CS | CONST_PERSISTENT);

    /* flag bits for parameter iflag in function swe_calc() */
    REGISTER_LONG_CONSTANT("SEFLG_JPLEPH", SEFLG_JPLEPH, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_SWIEPH", SEFLG_SWIEPH, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_MOSEPH", SEFLG_MOSEPH, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SEFLG_HELCTR", SEFLG_HELCTR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_TRUEPOS", SEFLG_TRUEPOS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_J2000", SEFLG_J2000, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_NONUT", SEFLG_NONUT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_SPEED3", SEFLG_SPEED3, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SEFLG_SPEED", SEFLG_SPEED, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_NOGDEFL", SEFLG_NOGDEFL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_NOABERR", SEFLG_NOABERR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_EQUATORIAL", SEFLG_EQUATORIAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_XYZ", SEFLG_XYZ, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_RADIANS", SEFLG_RADIANS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_BARYCTR", SEFLG_BARYCTR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_TOPOCTR", SEFLG_TOPOCTR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_SIDEREAL", SEFLG_SIDEREAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_ICRS", SEFLG_ICRS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_DPSIDEPS_1980", SEFLG_DPSIDEPS_1980, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_JPLHOR", SEFLG_JPLHOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_JPLHOR_APPROX", SEFLG_JPLHOR_APPROX, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_CENTER_BODY", SEFLG_CENTER_BODY, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SEFLG_TEST_PLMOON", SEFLG_TEST_PLMOON, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SE_SIDBITS", SE_SIDBITS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDBIT_ECL_T0", SE_SIDBIT_ECL_T0, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDBIT_SSY_PLANE", SE_SIDBIT_SSY_PLANE, CONST_CS | CONST_PERSISTENT);

    /* sidereal modes (ayanamsas) */
    REGISTER_LONG_CONSTANT("SE_SIDM_FAGAN_BRADLEY", SE_SIDM_FAGAN_BRADLEY, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_LAHIRI", SE_SIDM_LAHIRI, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_DELUCE", SE_SIDM_DELUCE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_RAMAN", SE_SIDM_RAMAN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_USHASHASHI", SE_SIDM_USHASHASHI, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_KRISHNAMURTI", SE_SIDM_KRISHNAMURTI, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_DJWHAL_KHUL", SE_SIDM_DJWHAL_KHUL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_YUKTESHWAR", SE_SIDM_YUKTESHWAR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_JN_BHASIN", SE_SIDM_JN_BHASIN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_BABYL_KUGLER1", SE_SIDM_BABYL_KUGLER1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_BABYL_KUGLER2", SE_SIDM_BABYL_KUGLER2, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_BABYL_KUGLER3", SE_SIDM_BABYL_KUGLER3, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_BABYL_HUBER", SE_SIDM_BABYL_HUBER, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_BABYL_ETPSC", SE_SIDM_BABYL_ETPSC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_ALDEBARAN_15TAU", SE_SIDM_ALDEBARAN_15TAU, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_HIPPARCHOS", SE_SIDM_HIPPARCHOS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_SASSANIAN", SE_SIDM_SASSANIAN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALCENT_0SAG", SE_SIDM_GALCENT_0SAG, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_J2000", SE_SIDM_J2000, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_J1900", SE_SIDM_J1900, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_B1950", SE_SIDM_B1950, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_SURYASIDDHANTA", SE_SIDM_SURYASIDDHANTA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_SURYASIDDHANTA_MSUN", SE_SIDM_SURYASIDDHANTA_MSUN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_ARYABHATA", SE_SIDM_ARYABHATA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_ARYABHATA_MSUN", SE_SIDM_ARYABHATA_MSUN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_SS_REVATI", SE_SIDM_SS_REVATI, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_SS_CITRA", SE_SIDM_SS_CITRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_TRUE_CITRA", SE_SIDM_TRUE_CITRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_TRUE_REVATI", SE_SIDM_TRUE_REVATI, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_TRUE_PUSHYA", SE_SIDM_TRUE_PUSHYA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALCENT_RGILBRAND", SE_SIDM_GALCENT_RGILBRAND, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALEQU_IAU1958", SE_SIDM_GALEQU_IAU1958, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALEQU_TRUE", SE_SIDM_GALEQU_TRUE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALEQU_MULA", SE_SIDM_GALEQU_MULA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALALIGN_MARDYKS", SE_SIDM_GALALIGN_MARDYKS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_TRUE_MULA", SE_SIDM_TRUE_MULA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALCENT_MULA_WILHELM", SE_SIDM_GALCENT_MULA_WILHELM, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_ARYABHATA_522", SE_SIDM_ARYABHATA_522, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_BABYL_BRITTON", SE_SIDM_BABYL_BRITTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_TRUE_SHEORAN", SE_SIDM_TRUE_SHEORAN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALCENT_COCHRANE", SE_SIDM_GALCENT_COCHRANE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_GALEQU_FIORENZA", SE_SIDM_GALEQU_FIORENZA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_VALENS_MOON", SE_SIDM_VALENS_MOON, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_LAHIRI_1940", SE_SIDM_LAHIRI_1940, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_LAHIRI_VP285", SE_SIDM_LAHIRI_VP285, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_KRISHNAMURTI_VP291", SE_SIDM_KRISHNAMURTI_VP291, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_LAHIRI_ICRC", SE_SIDM_LAHIRI_ICRC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SIDM_USER", SE_SIDM_USER, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("SE_SIDBIT_ECL_DATE", SE_SIDBIT_ECL_DATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NSIDM_PREDEF", SE_NSIDM_PREDEF, CONST_CS | CONST_PERSISTENT);

    /* used for swe_nod_aps(): */
    REGISTER_LONG_CONSTANT("SE_NODBIT_MEAN", SE_NODBIT_MEAN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NODBIT_OSCU", SE_NODBIT_OSCU, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NODBIT_OSCU_BAR", SE_NODBIT_OSCU_BAR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_NODBIT_FOPOINT", SE_NODBIT_FOPOINT, CONST_CS | CONST_PERSISTENT);

    /* default ephemeris used when no ephemeris flagbit is set */
    REGISTER_LONG_CONSTANT("SEFLG_DEFAULTEPH", SEFLG_DEFAULTEPH, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MAX_STNAME", SE_MAX_STNAME, CONST_CS | CONST_PERSISTENT);

    /* defines for eclipse computations */
    REGISTER_LONG_CONSTANT("SE_ECL_CENTRAL", SE_ECL_CENTRAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_NONCENTRAL", SE_ECL_NONCENTRAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_TOTAL", SE_ECL_TOTAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_ANNULAR", SE_ECL_ANNULAR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_PARTIAL", SE_ECL_PARTIAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_ANNULAR_TOTAL", SE_ECL_ANNULAR_TOTAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_PENUMBRAL", SE_ECL_PENUMBRAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_VISIBLE", SE_ECL_VISIBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_MAX_VISIBLE", SE_ECL_MAX_VISIBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_1ST_VISIBLE", SE_ECL_1ST_VISIBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_2ND_VISIBLE", SE_ECL_2ND_VISIBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_3RD_VISIBLE", SE_ECL_3RD_VISIBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_4TH_VISIBLE", SE_ECL_4TH_VISIBLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_ECL_ONE_TRY", SE_ECL_ONE_TRY, CONST_CS | CONST_PERSISTENT);

    /* for swe_rise_transit() */
    REGISTER_LONG_CONSTANT("SE_CALC_RISE", SE_CALC_RISE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_CALC_SET", SE_CALC_SET, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_CALC_MTRANSIT", SE_CALC_MTRANSIT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_CALC_ITRANSIT", SE_CALC_ITRANSIT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_DISC_CENTER", SE_BIT_DISC_CENTER, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_DISC_BOTTOM", SE_BIT_DISC_BOTTOM, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_NO_REFRACTION", SE_BIT_NO_REFRACTION, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_CIVIL_TWILIGHT", SE_BIT_CIVIL_TWILIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_NAUTIC_TWILIGHT", SE_BIT_NAUTIC_TWILIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_ASTRO_TWILIGHT", SE_BIT_ASTRO_TWILIGHT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_FIXED_DISC_SIZE", SE_BIT_FIXED_DISC_SIZE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_GEOCTR_NO_ECL_LAT", SE_BIT_GEOCTR_NO_ECL_LAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_BIT_HINDU_RISING", SE_BIT_HINDU_RISING, CONST_CS | CONST_PERSISTENT);

    /* for swe_azalt() and swe_azalt_rev() */
    REGISTER_LONG_CONSTANT("SE_ECL2HOR", SE_ECL2HOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_EQU2HOR", SE_EQU2HOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HOR2ECL", SE_HOR2ECL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HOR2EQU", SE_HOR2EQU, CONST_CS | CONST_PERSISTENT);

    /* for swe_refrac() */
    REGISTER_LONG_CONSTANT("SE_TRUE_TO_APP", SE_TRUE_TO_APP, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_APP_TO_TRUE", SE_APP_TO_TRUE, CONST_CS | CONST_PERSISTENT);

    /* for swe_set_tid_acc() */
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE200", SE_TIDAL_DE200, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE403", SE_TIDAL_DE403, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE404", SE_TIDAL_DE404, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE405", SE_TIDAL_DE405, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE406", SE_TIDAL_DE406, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE421", SE_TIDAL_DE421, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE422", SE_TIDAL_DE422, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE430", SE_TIDAL_DE430, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE431", SE_TIDAL_DE431, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DE441", SE_TIDAL_DE441, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_26", SE_TIDAL_26, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_STEPHENSON_2016", SE_TIDAL_STEPHENSON_2016, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_DEFAULT", SE_TIDAL_DEFAULT, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_TIDAL_AUTOMATIC", SE_TIDAL_AUTOMATIC, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_MOSEPH", SE_TIDAL_MOSEPH, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_SWIEPH", SE_TIDAL_SWIEPH, CONST_CS | CONST_PERSISTENT);
    REGISTER_DOUBLE_CONSTANT("SE_TIDAL_JPLEPH", SE_TIDAL_JPLEPH, CONST_CS | CONST_PERSISTENT);

    /* for swe_split_deg() */
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_ROUND_SEC", SE_SPLIT_DEG_ROUND_SEC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_ROUND_MIN", SE_SPLIT_DEG_ROUND_MIN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_ROUND_DEG", SE_SPLIT_DEG_ROUND_DEG, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_ZODIACAL", SE_SPLIT_DEG_ZODIACAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_NAKSHATRA", SE_SPLIT_DEG_NAKSHATRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_KEEP_SIGN", SE_SPLIT_DEG_KEEP_SIGN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_SPLIT_DEG_KEEP_DEG", SE_SPLIT_DEG_KEEP_DEG, CONST_CS | CONST_PERSISTENT);

    /* for swe_heliacal_ut() */
    REGISTER_LONG_CONSTANT("SE_HELIACAL_RISING", SE_HELIACAL_RISING, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HELIACAL_SETTING", SE_HELIACAL_SETTING, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_EVENING_FIRST", SE_EVENING_FIRST, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_MORNING_LAST", SE_MORNING_LAST, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HELFLAG_OPTICAL_PARAMS", SE_HELFLAG_OPTICAL_PARAMS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HELFLAG_NO_DETAILS", SE_HELFLAG_NO_DETAILS, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HELFLAG_VISLIM_DARK", SE_HELFLAG_VISLIM_DARK, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("SE_HELFLAG_VISLIM_NOMOON", SE_HELFLAG_VISLIM_NOMOON, CONST_CS | CONST_PERSISTENT);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(swephp)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(swephp)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(swephp)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(swephp)
{
    char version[255];

    swe_version(version);
    php_info_print_table_start();
    php_info_print_table_header(2, "swephp support", "enabled");
    php_info_print_table_row(2, "extension version", SWEPH_EXTENSION_VERSION);
    php_info_print_table_row(2, "library (libswe.a) version", version);
    php_info_print_table_row(2, "default ephemeris file path", SE_EPHE_PATH);
    php_info_print_table_end();
}
/* }}} */

/* {{{ Module Entry Definition
 */
zend_module_entry swephp_module_entry = {
    STANDARD_MODULE_HEADER,
    "swephp",
    ext_functions, // Nutzt direkt das generierte ext_functions-Array aus swephp_arginfo.h
    PHP_MINIT(swephp),
    PHP_MSHUTDOWN(swephp),
    PHP_RINIT(swephp),
    PHP_RSHUTDOWN(swephp),
    PHP_MINFO(swephp),
    SWEPH_EXTENSION_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SWEPHP
ZEND_GET_MODULE(swephp)
#endif

#ifndef SWI_STAR_LENGTH
# define SWI_STAR_LENGTH 40
#endif
#define MAX_FIXSTAR_NAME (SWI_STAR_LENGTH)

/* =========================================================================
 *  FUNCTION IMPLEMENTATIONS
 * ========================================================================= */

PHP_FUNCTION(swe_calc)
{
    int rc;
    zend_long ipl, iflag;
    double tjd_et, xx[6];
    char serr[AS_MAXCH];
    int i;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dll", &tjd_et, &ipl, &iflag) == FAILURE) {
       return;
    }
    rc = swe_calc(tjd_et, (int)ipl, (int)iflag, xx, serr);

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_calc_ut)
{
    int rc;
    zend_long ipl, iflag;
    double tjd_ut, xx[6];
    char serr[AS_MAXCH];
    int i;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dll", &tjd_ut, &ipl, &iflag) == FAILURE) {
       return;
    }
    rc = swe_calc_ut(tjd_ut, (int)ipl, (int)iflag, xx, serr);

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_calc_pctr)
{
    int rc;
    zend_long ipl, iflag, iplctr;
    double tjd_et, xx[6];
    char serr[AS_MAXCH];
    int i;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlll", &tjd_et, &ipl, &iplctr, &iflag) == FAILURE) {
       return;
    }
    rc = swe_calc_pctr(tjd_et, (int)ipl, (int)iplctr, (int)iflag, xx, serr);

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_solcross)
{
    int rc = 0;
    zend_long iflag;
    double jd_et, jx, x2cross;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddl", &x2cross, &jd_et, &iflag) == FAILURE) {
       return;
    }
    jx = swe_solcross(x2cross, jd_et, (int)iflag, serr);
    if (*serr != '\0' || jx < jd_et) {
      rc = ERR;
    }
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
}

PHP_FUNCTION(swe_solcross_ut)
{
    int rc = 0;
    zend_long iflag;
    double jd_ut, jx, x2cross;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddl", &x2cross, &jd_ut, &iflag) == FAILURE) {
       return;
    }
    jx = swe_solcross_ut(x2cross, jd_ut, (int)iflag, serr);
    if (*serr != '\0' || jx < jd_ut) {
      rc = ERR;
    }
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
}

PHP_FUNCTION(swe_mooncross)
{
    int rc = 0;
    zend_long iflag;
    double jd_et, jx, x2cross;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddl", &x2cross, &jd_et, &iflag) == FAILURE) {
       return;
    }
    jx = swe_mooncross(x2cross, jd_et, (int)iflag, serr);
    if (*serr != '\0' || jx < jd_et) {
      rc = ERR;
    }
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
}

PHP_FUNCTION(swe_mooncross_ut)
{
    int rc = 0;
    zend_long iflag;
    double jd_ut, jx, x2cross;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddl", &x2cross, &jd_ut, &iflag) == FAILURE) {
       return;
    }
    jx = swe_mooncross_ut(x2cross, jd_ut, (int)iflag, serr);
    if (*serr != '\0' || jx < jd_ut) {
      rc = ERR;
    }
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
}

PHP_FUNCTION(swe_mooncross_node)
{
    int rc = 0;
    zend_long iflag;
    double jd_et, jx, xlon, xlat;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &jd_et, &iflag) == FAILURE) {
       return;
    }
    jx = swe_mooncross_node(jd_et, (int)iflag, &xlon, &xlat, serr);
    if (*serr != '\0' || jx < jd_et) {
      rc = ERR;
    }
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
    add_assoc_double(return_value, "xlon", xlon);
    add_assoc_double(return_value, "xlat", xlat);
}

PHP_FUNCTION(swe_mooncross_node_ut)
{
    int rc = 0;
    zend_long iflag;
    double jd_ut, jx, xlon, xlat;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &jd_ut, &iflag) == FAILURE) {
       return;
    }
    jx = swe_mooncross_node_ut(jd_ut, (int)iflag, &xlon, &xlat, serr);
    if (*serr != '\0' || jx < jd_ut) {
      rc = ERR;
    }
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
    add_assoc_double(return_value, "xlon", xlon);
    add_assoc_double(return_value, "xlat", xlat);
}

PHP_FUNCTION(swe_helio_cross)
{
    int rc = 0;
    zend_long ipl, iflag, dir;
    double jd_et, jx, x2cross;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lddll", &ipl, &x2cross, &jd_et, &iflag, &dir) == FAILURE) {
       return;
    }
    rc = swe_helio_cross((int)ipl, x2cross, jd_et, (int)iflag, (int)dir, &jx, serr);
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
}

PHP_FUNCTION(swe_helio_cross_ut)
{
    int rc = 0;
    zend_long ipl, iflag, dir;
    double jd_ut, jx, x2cross;
    char serr[AS_MAXCH];
    *serr = '\0';
    jx = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lddll", &ipl, &x2cross, &jd_ut, &iflag, &dir) == FAILURE) {
       return;
    }
    rc = swe_helio_cross_ut((int)ipl, x2cross, jd_ut, (int)iflag, (int)dir, &jx, serr);
    array_init(return_value);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "jx", jx);
}

PHP_FUNCTION(swe_fixstar)
{
    int rc;
    zend_long iflag;
    double tjd_et, xx[6];
    char *star_ptr = NULL;
    size_t star_len;
    char star[MAX_FIXSTAR_NAME + 1], serr[AS_MAXCH];
    int i;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sdl", &star_ptr, &star_len, &tjd_et, &iflag) == FAILURE) {
       return;
    }
    if (star_len > MAX_FIXSTAR_NAME) star_ptr[MAX_FIXSTAR_NAME] = '\0';
    strcpy(star, star_ptr);
    rc = swe_fixstar(star, tjd_et, (int)iflag, xx, serr);
    if (!(iflag & SEFLG_SPEED)) {
       for (i = 3; i < 6; i++) xx[i] = 0;
    }

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "star", star);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_fixstar2)
{
    int rc;
    zend_long iflag;
    double tjd_et, xx[6];
    char *star_ptr = NULL;
    size_t star_len;
    char star[MAX_FIXSTAR_NAME + 1], serr[AS_MAXCH];
    int i;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sdl", &star_ptr, &star_len, &tjd_et, &iflag) == FAILURE) {
       return;
    }
    if (star_len > MAX_FIXSTAR_NAME) star_ptr[MAX_FIXSTAR_NAME] = '\0';
    strcpy(star, star_ptr);
    rc = swe_fixstar2(star, tjd_et, (int)iflag, xx, serr);

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "star", star);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_fixstar_ut)
{
    int rc;
    zend_long iflag;
    double tjd_ut, xx[6];
    char *star_ptr = NULL;
    size_t star_len;
    char star[MAX_FIXSTAR_NAME + 1], serr[AS_MAXCH];
    int i;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sdl", &star_ptr, &star_len, &tjd_ut, &iflag) == FAILURE) {
       return;
    }
    if (star_len > MAX_FIXSTAR_NAME) star_ptr[MAX_FIXSTAR_NAME] = '\0';
    strcpy(star, star_ptr);
    rc = swe_fixstar_ut(star, tjd_ut, (int)iflag, xx, serr);
    if (!(iflag & SEFLG_SPEED)) {
       for (i = 3; i < 6; i++) xx[i] = 0;
    }

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "star", star);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_fixstar2_ut)
{
    int rc;
    zend_long iflag;
    double tjd_ut, xx[6];
    char *star_ptr = NULL;
    size_t star_len;
    char star[MAX_FIXSTAR_NAME + 1], serr[AS_MAXCH];
    int i;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sdl", &star_ptr, &star_len, &tjd_ut, &iflag) == FAILURE) {
       return;
    }
    if (star_len > MAX_FIXSTAR_NAME) star_ptr[MAX_FIXSTAR_NAME] = '\0';
    strcpy(star, star_ptr);
    rc = swe_fixstar2_ut(star, tjd_ut, (int)iflag, xx, serr);

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xx[i]);
    add_assoc_string(return_value, "star", star);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_fixstar_mag)
{
    int rc;
    double dmag;
    char *star_ptr = NULL;
    size_t star_len;
    char star[MAX_FIXSTAR_NAME + 1], serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &star_ptr, &star_len) == FAILURE) {
       return;
    }
    if (star_len > MAX_FIXSTAR_NAME) star_ptr[MAX_FIXSTAR_NAME] = '\0';
    strcpy(star, star_ptr);
    rc = swe_fixstar_mag(star, &dmag, serr);

    array_init(return_value);
    if (rc >= 0)
       add_assoc_double(return_value, "mag", dmag);
    add_assoc_string(return_value, "star", star);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_fixstar2_mag)
{
    int rc;
    double dmag;
    char *star_ptr = NULL;
    size_t star_len;
    char star[MAX_FIXSTAR_NAME + 1], serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &star_ptr, &star_len) == FAILURE) {
       return;
    }
    if (star_len > MAX_FIXSTAR_NAME) star_ptr[MAX_FIXSTAR_NAME] = '\0';
    strcpy(star, star_ptr);
    rc = swe_fixstar2_mag(star, &dmag, serr);

    array_init(return_value);
    if (rc >= 0)
       add_assoc_double(return_value, "mag", dmag);
    add_assoc_string(return_value, "star", star);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_close)
{
    swe_close();
    RETURN_NULL();
}

PHP_FUNCTION(swe_set_ephe_path)
{
    char *arg = NULL;
    size_t arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s!", &arg, &arg_len) == FAILURE) {
       return;
    }

    swe_set_ephe_path(arg);
    RETURN_NULL();
}

PHP_FUNCTION(swe_set_jpl_file)
{
    char *arg = NULL;
    size_t arg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
       return;
    }

    swe_set_jpl_file(arg);
    RETURN_NULL();
}

PHP_FUNCTION(swe_get_planet_name)
{
    zend_long ipl;
    char name[AS_MAXCH];

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &ipl) == FAILURE) {
       return;
    }

    swe_get_planet_name((int)ipl, name);
    RETURN_STRING(name);
}

PHP_FUNCTION(swe_set_topo)
{
    double geo_lon, geo_lat, geo_alt;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd", &geo_lon, &geo_lat, &geo_alt) == FAILURE) {
       return;
    }
    swe_set_topo(geo_lon, geo_lat, geo_alt);
    RETURN_NULL();
}

PHP_FUNCTION(swe_set_sid_mode)
{
    zend_long sid_mode;
    double t0, ayan_t0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ldd", &sid_mode, &t0, &ayan_t0) == FAILURE) {
       return;
    }
    swe_set_sid_mode((int)sid_mode, t0, ayan_t0);
    RETURN_NULL();
}

PHP_FUNCTION(swe_get_ayanamsa)
{
    double tjd_et;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &tjd_et) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_get_ayanamsa(tjd_et));
}

PHP_FUNCTION(swe_get_ayanamsa_ex)
{
    double tjd_et, daya;
    zend_long iflag;
    int rc;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &tjd_et, &iflag) == FAILURE) {
       return;
    }

    rc = swe_get_ayanamsa_ex(tjd_et, (int)iflag, &daya, serr);
    if (!(iflag & SEFLG_NONUT))
       rc &= (~SEFLG_NONUT);

    array_init(return_value);
    add_assoc_double(return_value, "daya", daya);
    add_assoc_long(return_value, "rc", rc);
    if (rc < 0)
       add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_get_ayanamsa_ut)
{
    double tjd_ut;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &tjd_ut) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_get_ayanamsa_ut(tjd_ut));
}

PHP_FUNCTION(swe_get_ayanamsa_ex_ut)
{
    double tjd_ut, daya;
    zend_long iflag;
    int rc;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &tjd_ut, &iflag) == FAILURE) {
       return;
    }

    rc = swe_get_ayanamsa_ex_ut(tjd_ut, (int)iflag, &daya, serr);
    if (!(iflag & SEFLG_NONUT))
       rc &= (~SEFLG_NONUT);

    array_init(return_value);
    add_assoc_double(return_value, "daya", daya);
    add_assoc_long(return_value, "rc", rc);
    if (rc < 0)
       add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_get_ayanamsa_name)
{
    zend_long isidmode;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &isidmode) == FAILURE) {
       return;
    }

    RETURN_STRING(swe_get_ayanamsa_name((int)isidmode));
}

PHP_FUNCTION(swe_version)
{
    char name[AS_MAXCH];
    RETURN_STRING(swe_version(name));
}

PHP_FUNCTION(swe_get_library_path)
{
    char path[AS_MAXCH];
    RETURN_STRING(swe_get_library_path(path));
}

PHP_FUNCTION(swe_get_current_file_data)
{
    zend_long ifno;
    int denum;
    double tfstart, tfend;
    char *a = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &ifno) == FAILURE) {
       return;
    }

    a = (char *)swe_get_current_file_data((int)ifno, &tfstart, &tfend, &denum);
    if (a == NULL) {
       RETURN_NULL();
    } else {
       array_init(return_value);
       add_assoc_string(return_value, "path", a);
       add_assoc_double(return_value, "tfstart", tfstart);
       add_assoc_double(return_value, "tfend", tfend);
       add_assoc_long(return_value, "denum", denum);
    }
}

PHP_FUNCTION(swe_date_conversion)
{
    size_t arg_len;
    int rc;
    zend_long year, month, day;
    double hour, tjd;
    char *gregflag = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lllds", &year, &month, &day, &hour, &gregflag, &arg_len) == FAILURE) {
       return;
    }
    if (arg_len < 1)
       RETURN_NULL();

    rc = swe_date_conversion((int)year, (int)month, (int)day, hour, gregflag[0], &tjd);
    if (rc == OK) {
       RETURN_DOUBLE(tjd);
    } else {
       RETURN_NULL();
    }
}

PHP_FUNCTION(swe_julday)
{
    zend_long year, month, day, gregflag = 1;
    double hour;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "llld|l", &year, &month, &day, &hour, &gregflag) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_julday((int)year, (int)month, (int)day, hour, (int)gregflag));
}

PHP_FUNCTION(swe_revjul)
{
    int year, month, day, ihour, imin, isec;
    zend_long gregflag = 1;
    double hour, jd, dsec;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d|l", &jd, &gregflag) == FAILURE) {
       return;
    }

    swe_revjul(jd, (int)gregflag, &year, &month, &day, &hour);

    dsec = (hour * 3600) + 0.00005;
    ihour = (int)floor(dsec / 3600);
    dsec -= ihour * 3600;
    imin = (int)floor(dsec / 60);
    dsec -= imin * 60;
    isec = (int)floor(dsec);

    array_init(return_value);
    add_assoc_long(return_value, "year", year);
    add_assoc_long(return_value, "month", month);
    add_assoc_long(return_value, "day", day);
    add_assoc_double(return_value, "hour", hour);
    add_assoc_long(return_value, "ihour", ihour);
    add_assoc_long(return_value, "imin", imin);
    add_assoc_long(return_value, "isec", isec);
    add_assoc_double(return_value, "dsec", dsec);
}

PHP_FUNCTION(swe_jdet_to_utc)
{
    double tjd_et;
    zend_long gregflag;
    int32 iyear, imonth, iday;
    int32 ihour, imin;
    double dsec;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &tjd_et, &gregflag) == FAILURE) {
       return;
    }
    swe_jdet_to_utc(tjd_et, (int32)gregflag, &iyear, &imonth, &iday, &ihour, &imin, &dsec);

    array_init(return_value);
    add_assoc_long(return_value, "year", iyear);
    add_assoc_long(return_value, "month", imonth);
    add_assoc_long(return_value, "day", iday);
    add_assoc_long(return_value, "hour", ihour);
    add_assoc_long(return_value, "min", imin);
    add_assoc_double(return_value, "sec", dsec);
}

PHP_FUNCTION(swe_jdut1_to_utc)
{
    double tjd_ut;
    zend_long gregflag;
    int32 iyear, imonth, iday;
    int32 ihour, imin;
    double dsec;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &tjd_ut, &gregflag) == FAILURE) {
       return;
    }
    swe_jdut1_to_utc(tjd_ut, (int32)gregflag, &iyear, &imonth, &iday, &ihour, &imin, &dsec);

    array_init(return_value);
    add_assoc_long(return_value, "year", iyear);
    add_assoc_long(return_value, "month", imonth);
    add_assoc_long(return_value, "day", iday);
    add_assoc_long(return_value, "hour", ihour);
    add_assoc_long(return_value, "min", imin);
    add_assoc_double(return_value, "sec", dsec);
}

PHP_FUNCTION(swe_utc_to_jd)
{
    zend_long gregflag;
    zend_long iyear, imonth, iday;
    zend_long ihour, imin;
    double dsec, dret[2];
    char serr[AS_MAXCH];
    int32 rc;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "llllldl", &iyear, &imonth, &iday, &ihour, &imin, &dsec, &gregflag) == FAILURE) {
       return;
    }
    rc = swe_utc_to_jd((int32)iyear, (int32)imonth, (int32)iday, (int32)ihour, (int32)imin, dsec, (int32)gregflag, dret, serr);

    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);
    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       add_index_double(return_value, 0, dret[0]);
       add_index_double(return_value, 1, dret[1]);
    }
}

PHP_FUNCTION(swe_utc_time_zone)
{
    zend_long iyear, imonth, iday;
    zend_long ihour, imin;
    double dsec, d_timezone;
    int32 iyear_out, imonth_out, iday_out, ihour_out, imin_out;
    double dsec_out;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "llllldd", &iyear, &imonth, &iday, &ihour, &imin, &dsec, &d_timezone) == FAILURE) {
       return;
    }
    swe_utc_time_zone((int32)iyear, (int32)imonth, (int32)iday, (int32)ihour, (int32)imin, dsec, d_timezone, &iyear_out, &imonth_out, &iday_out, &ihour_out, &imin_out, &dsec_out);

    array_init(return_value);
    add_assoc_long(return_value, "year", iyear_out);
    add_assoc_long(return_value, "month", imonth_out);
    add_assoc_long(return_value, "day", iday_out);
    add_assoc_long(return_value, "hour", ihour_out);
    add_assoc_long(return_value, "min", imin_out);
    add_assoc_double(return_value, "sec", dsec_out);
}

PHP_FUNCTION(swe_houses)
{
    size_t hsys_len;
    int rc;
    char *hsys = NULL;
    double tjd_ut, geolat, geolon;
    double cusps[37], ascmc[10];
    int i, houses;
    zval cusps_arr, ascmc_arr;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddds", &tjd_ut, &geolat, &geolon, &hsys, &hsys_len) == FAILURE) {
       return;
    }
    if (hsys_len < 1) return;

    rc = swe_houses(tjd_ut, geolat, geolon, hsys[0], cusps, ascmc);

    array_init(return_value);
    array_init(&cusps_arr);

    houses = (hsys[0] == 'G') ? 37 : 13;

    for(i = 0; i < houses; i++)
       add_index_double(&cusps_arr, i, cusps[i]);

    array_init(&ascmc_arr);
    for(i = 0; i < 10; i++)
       add_index_double(&ascmc_arr, i, ascmc[i]);

    add_assoc_zval(return_value, "cusps", &cusps_arr);
    add_assoc_zval(return_value, "ascmc", &ascmc_arr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_houses_ex)
{
    size_t hsys_len;
    int rc;
    char *hsys = NULL;
    double tjd_ut, geolat, geolon;
    double cusps[37], ascmc[10];
    int i, houses;
    zend_long iflag;
    zval cusps_arr, ascmc_arr;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dldds", &tjd_ut, &iflag, &geolat, &geolon, &hsys, &hsys_len) == FAILURE) {
       return;
    }
    if (hsys_len < 1) return;

    rc = swe_houses_ex(tjd_ut, (int)iflag, geolat, geolon, hsys[0], cusps, ascmc);

    array_init(return_value);
    array_init(&cusps_arr);

    houses = (hsys[0] == 'G') ? 37 : 13;

    for(i = 0; i < houses; i++)
       add_index_double(&cusps_arr, i, cusps[i]);

    array_init(&ascmc_arr);
    for(i = 0; i < 10; i++)
       add_index_double(&ascmc_arr, i, ascmc[i]);

    add_assoc_zval(return_value, "cusps", &cusps_arr);
    add_assoc_zval(return_value, "ascmc", &ascmc_arr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_houses_ex2)
{
    size_t hsys_len;
    int rc;
    char *hsys = NULL;
    double tjd_ut, geolat, geolon;
    double cusps[37], ascmc[10], cusp_speed[37], ascmc_speed[10];
    int i, houses;
    zend_long iflag;
    zval cusps_arr, ascmc_arr, cusp_speed_arr, ascmc_speed_arr;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dldds", &tjd_ut, &iflag, &geolat, &geolon, &hsys, &hsys_len) == FAILURE) {
       return;
    }
    if (hsys_len < 1) return;

    rc = swe_houses_ex2(tjd_ut, (int)iflag, geolat, geolon, hsys[0], cusps, ascmc, cusp_speed, ascmc_speed, serr);

    array_init(return_value);
    array_init(&cusps_arr);
    array_init(&cusp_speed_arr);

    houses = (hsys[0] == 'G') ? 37 : 13;

    for (i = 0; i < houses; i++) {
        add_index_double(&cusps_arr, i, cusps[i]);
        add_index_double(&cusp_speed_arr, i, cusp_speed[i]);
    }

    array_init(&ascmc_arr);
    array_init(&ascmc_speed_arr);

    for(i = 0; i < 10; i++) {
        add_index_double(&ascmc_arr, i, ascmc[i]);
        add_index_double(&ascmc_speed_arr, i, ascmc_speed[i]);
    }

    add_assoc_zval(return_value, "cusps", &cusps_arr);
    add_assoc_zval(return_value, "ascmc", &ascmc_arr);
    add_assoc_zval(return_value, "cusp_speed", &cusp_speed_arr);
    add_assoc_zval(return_value, "ascmc_speed", &ascmc_speed_arr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_houses_armc)
{
    size_t hsys_len;
    int rc;
    char *hsys = NULL;
    double armc, geolat, eps;
    double cusps[37], ascmc[10];
    int i, houses;
    zval cusps_arr, ascmc_arr;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddds", &armc, &geolat, &eps, &hsys, &hsys_len) == FAILURE) {
       return;
    }
    if (hsys_len < 1) return;

    rc = swe_houses_armc(armc, geolat, eps, hsys[0], cusps, ascmc);

    array_init(return_value);
    array_init(&cusps_arr);

    houses = (hsys[0] == 'G') ? 37 : 13;

    for(i = 0; i < houses; i++)
       add_index_double(&cusps_arr, i, cusps[i]);

    array_init(&ascmc_arr);
    for(i = 0; i < 10; i++)
       add_index_double(&ascmc_arr, i, ascmc[i]);

    add_assoc_zval(return_value, "cusps", &cusps_arr);
    add_assoc_zval(return_value, "ascmc", &ascmc_arr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_houses_armc_ex2)
{
    size_t hsys_len;
    int rc;
    char *hsys = NULL;
    double armc, geolat, eps;
    double cusps[37], ascmc[10], cusp_speed[37], ascmc_speed[10];
    int i, houses;
    zval cusps_arr, ascmc_arr, cusp_speed_arr, ascmc_speed_arr;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddds", &armc, &geolat, &eps, &hsys, &hsys_len) == FAILURE) {
       return;
    }
    if (hsys_len < 1) return;

    rc = swe_houses_armc_ex2(armc, geolat, eps, hsys[0], cusps, ascmc, cusp_speed, ascmc_speed, serr);

    array_init(return_value);
    array_init(&cusps_arr);
    array_init(&cusp_speed_arr);

    houses = (hsys[0] == 'G') ? 37 : 13;

    for (i = 0; i < houses; i++) {
        add_index_double(&cusps_arr, i, cusps[i]);
        add_index_double(&cusp_speed_arr, i, cusp_speed[i]);
    }

    array_init(&ascmc_arr);
    array_init(&ascmc_speed_arr);

    for (i = 0; i < 10; i++) {
        add_index_double(&ascmc_arr, i, ascmc[i]);
        add_index_double(&ascmc_speed_arr, i, ascmc_speed[i]);
    }

    add_assoc_zval(return_value, "cusps", &cusps_arr);
    add_assoc_zval(return_value, "ascmc", &ascmc_arr);
    add_assoc_zval(return_value, "cusp_speed", &cusp_speed_arr);
    add_assoc_zval(return_value, "ascmc_speed", &ascmc_speed_arr);
    add_assoc_long(return_value, "rc", rc);
    add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_house_pos)
{
    size_t hsys_len;
    char *hsys = NULL;
    double armc, geolat, eps, xpin[2], rc;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddsdd", &armc, &geolat, &eps, &hsys, &hsys_len, &xpin[0], &xpin[1]) == FAILURE) {
       return;
    }
    if (hsys_len < 1) return;

    rc = swe_house_pos(armc, geolat, eps, hsys[0], xpin, serr);

    if ((rc >= 1.0) && (rc < 13.0)) {
       RETURN_DOUBLE(rc);
    } else {
       RETURN_STRING(serr);
    }
}

PHP_FUNCTION(swe_house_name)
{
    size_t hsys_len;
    char *hsys = NULL;
    char *name;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &hsys, &hsys_len) == FAILURE) {
       return;
    }

    if (hsys_len < 1) return;
    name = (char*)swe_house_name(hsys[0]);

    RETURN_STRING(name);
}

PHP_FUNCTION(swe_gauquelin_sector)
{
    size_t s_len;
    zend_long ipl, iflag, imeth;
    int rc;
    char *starname = NULL;
    double t_ut, geopos[3], atpress, attemp, dgsect;
    char serr[AS_MAXCH];
    char star[AS_MAXCH];
    *serr = '\0';
    *star = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlsllddddd", &t_ut, &ipl, &starname, &s_len, &iflag, &imeth, &geopos[0], &geopos[1], &geopos[2], &atpress, &attemp) == FAILURE) {
       return;
    }
    if (starname != NULL && s_len > 0)
       strcpy(star, starname);
    rc = swe_gauquelin_sector(t_ut, (int32)ipl, star, (int32)iflag, (int32)imeth, geopos, atpress, attemp, &dgsect, serr);

    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);
    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       add_assoc_double(return_value, "gsect", dgsect);
       if (starname != NULL && s_len > 0)
          add_assoc_string(return_value, "star", star);
    }
}

PHP_FUNCTION(swe_sol_eclipse_where)
{
    zend_long ifl;
    int rc;
    double tjd_ut, geopos[10], attr[20];
    char serr[AS_MAXCH];
    int i;
    zval geopos_arr, attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &tjd_ut, &ifl) == FAILURE) {
       return;
    }
    rc = swe_sol_eclipse_where(tjd_ut, (int32)ifl, geopos, attr, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);
    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&geopos_arr);
       for(i = 0; i < 2; i++)
          add_index_double(&geopos_arr, i, geopos[i]);
       array_init(&attr_arr);
       for(i = 0; i < 20; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "geopos", &geopos_arr);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_lun_occult_where)
{
    zend_long ipl, ifl;
    size_t s_len;
    double tjd_ut, geopos[10], attr[20];
    char serr[AS_MAXCH], *starname = NULL;
    char star[AS_MAXCH];
    int i, rc;
    zval geopos_arr, attr_arr;
    *serr = '\0';
    *star = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlsd", &tjd_ut, &ipl, &starname, &s_len, &ifl) == FAILURE) {
       return;
    }
    if (starname != NULL && s_len > 0)
       strcpy(star, starname);
    rc = swe_lun_occult_where(tjd_ut, (int32)ipl, star, (int32)ifl, geopos, attr, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&geopos_arr);
       for(i = 0; i < 2; i++)
          add_index_double(&geopos_arr, i, geopos[i]);
       array_init(&attr_arr);
       for(i = 0; i < 8; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "geopos", &geopos_arr);
       add_assoc_zval(return_value, "attr", &attr_arr);
       if (starname != NULL && s_len > 0)
          add_assoc_string(return_value, "star", star);
    }
}

PHP_FUNCTION(swe_sol_eclipse_how)
{
    zend_long ifl;
    int rc;
    double tjd_ut, geopos[3], attr[20];
    char serr[AS_MAXCH];
    int i;
    zval attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlddd", &tjd_ut, &ifl, &geopos[0], &geopos[1], &geopos[2]) == FAILURE) {
       return;
    }
    rc = swe_sol_eclipse_how(tjd_ut, (int32)ifl, geopos, attr, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&attr_arr);
       for(i = 0; i < 20; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_sol_eclipse_when_loc)
{
    zend_long ifl, backward;
    int rc;
    double tjd_start, geopos[3], tret[10], attr[20];
    char serr[AS_MAXCH];
    int i;
    zval tret_arr, attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dldddl", &tjd_start, &ifl, &geopos[0], &geopos[1], &geopos[2], &backward) == FAILURE) {
       return;
    }
    rc = swe_sol_eclipse_when_loc(tjd_start, (int32)ifl, geopos, tret, attr, (int32)backward, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 7; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
       array_init(&attr_arr);
       for(i = 0; i < 11; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_lun_occult_when_loc)
{
    zend_long backward, ipl, ifl;
    int rc;
    size_t s_len;
    double tjd_start, geopos[3], tret[10], attr[11];
    char serr[AS_MAXCH], star[MAX_FIXSTAR_NAME + 1], *starname = NULL;
    int i;
    zval tret_arr, attr_arr;
    *serr = '\0';
    *star = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlsldddl", &tjd_start, &ipl, &starname, &s_len, &ifl, &geopos[0], &geopos[1], &geopos[2], &backward) == FAILURE) {
       return;
    }
    if (starname != NULL && s_len > 0) {
        if (s_len > MAX_FIXSTAR_NAME) starname[MAX_FIXSTAR_NAME] = '\0';
       strcpy(star, starname);
    }
    rc = swe_lun_occult_when_loc(tjd_start, (int32)ipl, star, (int32)ifl, geopos, tret, attr, (int32)backward, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);
    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 8; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
       array_init(&attr_arr);
       for(i = 0; i < 10; i++)
          add_index_double(&attr_arr, i, attr[i]);
       if (starname != NULL && s_len > 0)
          add_assoc_string(return_value, "star", star);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_sol_eclipse_when_glob)
{
    zend_long ifl, ifltype, backward;
    double tjd_start, tret[10];
    char serr[AS_MAXCH];
    int rc, i;
    zval tret_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlll", &tjd_start, &ifl, &ifltype, &backward) == FAILURE) {
       return;
    }
    rc = swe_sol_eclipse_when_glob(tjd_start, (int32)ifl, (int32)ifltype, tret, (int32)backward, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 10; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
    }
}

PHP_FUNCTION(swe_lun_occult_when_glob)
{
    zend_long backward, ipl, ifl, ifltype;
    size_t s_len = 0;
    double tjd_start, tret[10];
    char serr[AS_MAXCH], *starname = NULL;
    char star[MAX_FIXSTAR_NAME + 1];
    int i, rc;
    zval tret_arr;
    *serr = '\0';
    *star = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlslll", &tjd_start, &ipl, &starname, &s_len, &ifl, &ifltype, &backward) == FAILURE) {
       return;
    }
    if (starname != NULL && s_len > 0) {
        if (s_len > MAX_FIXSTAR_NAME) starname[MAX_FIXSTAR_NAME] = '\0';
       strcpy(star, starname);
    }
    rc = swe_lun_occult_when_glob(tjd_start, (int32)ipl, star, (int32)ifl, (int32)ifltype, tret, (int32)backward, serr);
    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 10; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
       if (starname != NULL && s_len > 0)
          add_assoc_string(return_value, "star", star);
    }
}

PHP_FUNCTION(swe_lun_eclipse_how)
{
    zend_long ifl;
    double tjd_ut, geopos[3], attr[20];
    char serr[AS_MAXCH];
    int i, rc;
    zval attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlddd", &tjd_ut, &ifl, &geopos[0], &geopos[1], &geopos[2]) == FAILURE) {
       return;
    }
    rc = swe_lun_eclipse_how(tjd_ut, (int32)ifl, geopos, attr, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&attr_arr);
       for(i = 0; i < 11; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_lun_eclipse_when)
{
    zend_long backward, ifl, ifltype;
    double tjd_start, tret[10];
    char serr[AS_MAXCH];
    int i, rc;
    zval tret_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlll", &tjd_start, &ifl, &ifltype, &backward) == FAILURE) {
       return;
    }
    rc = swe_lun_eclipse_when(tjd_start, (int32)ifl, (int32)ifltype, tret, (int32)backward, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);
    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 8; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
    }
}

PHP_FUNCTION(swe_lun_eclipse_when_loc)
{
    zend_long backward, ifl;
    double tjd_start, geopos[3], tret[10], attr[20];
    char serr[AS_MAXCH];
    int i, rc;
    zval tret_arr, attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dldddl", &tjd_start, &ifl, &geopos[0], &geopos[1], &geopos[2], &backward) == FAILURE) {
       return;
    }
    rc = swe_lun_eclipse_when_loc(tjd_start, (int32)ifl, geopos, tret, attr, (int32)backward, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 10; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);

       array_init(&attr_arr);
       for(i = 0; i < 11; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_pheno)
{
    zend_long ipl, iflag;
    double tjd_et, attr[20];
    char serr[AS_MAXCH];
    int i, rc;
    zval attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dll", &tjd_et, &ipl, &iflag) == FAILURE) {
       return;
    }
    rc = swe_pheno(tjd_et, (int32)ipl, (int32)iflag, attr, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&attr_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_pheno_ut)
{
    int rc;
    zend_long ipl, iflag;
    double tjd_ut, attr[20];
    char serr[AS_MAXCH];
    int i;
    zval attr_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dll", &tjd_ut, &ipl, &iflag) == FAILURE) {
       return;
    }
    rc = swe_pheno_ut(tjd_ut, (int32)ipl, (int32)iflag, attr, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&attr_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&attr_arr, i, attr[i]);
       add_assoc_zval(return_value, "attr", &attr_arr);
    }
}

PHP_FUNCTION(swe_refrac)
{
    double outalt;
    zend_long calc_flag;
    double inalt, atpress, attemp;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddl", &inalt, &atpress, &attemp, &calc_flag) == FAILURE) {
       return;
    }
    outalt = swe_refrac(inalt, atpress, attemp, (int32)calc_flag);
    RETURN_DOUBLE(outalt);
}

PHP_FUNCTION(swe_refrac_extended)
{
    int rc, i;
    zend_long calc_flag;
    double inalt, geoalt, atpress, lapse_rate, attemp;
    double dret[4];

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddddl", &inalt, &geoalt, &atpress, &attemp, &lapse_rate, &calc_flag) == FAILURE) {
       return;
    }
    rc = swe_refrac_extended(inalt, geoalt, atpress, attemp, lapse_rate, (int32)calc_flag, dret);

    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);
    for(i = 0; i < 4; i++)
       add_index_double(return_value, i, dret[i]);
    add_assoc_double(return_value, "retflag", rc);
}

PHP_FUNCTION(swe_heliacal_ut)
{
    int rc;
    double tjdstart, dgeo[3], datm[4], dobs[6], dret[3];
    char serr[AS_MAXCH], *objectname = NULL;
    int i;
    size_t olen;
    zend_long event_type, helflag;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddddddddddddddsll", &tjdstart, &dgeo[0], &dgeo[1], &dgeo[2], &datm[0], &datm[1], &datm[2], &datm[3], &dobs[0], &dobs[1], &dobs[2], &dobs[3], &dobs[4], &dobs[5], &objectname, &olen, &event_type, &helflag) == FAILURE) {
       return;
    }
    rc = swe_heliacal_ut(tjdstart, dgeo, datm, dobs, objectname, (int32)event_type, (int32)helflag, dret, serr);
    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);
    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       for(i = 0; i < 3 ; i++)
          add_index_double(return_value, i, dret[i]);
    }
}

PHP_FUNCTION(swe_heliacal_pheno_ut)
{
    int rc;
    double tjdstart, dgeo[3], datm[4], dobs[6], darr[50];
    char serr[AS_MAXCH], *objectname = NULL;
    int i;
    size_t olen;
    zend_long event_type, helflag;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddddddddddddddsll", &tjdstart, &dgeo[0], &dgeo[1], &dgeo[2], &datm[0], &datm[1], &datm[2], &datm[3], &dobs[0], &dobs[1], &dobs[2], &dobs[3], &dobs[4], &dobs[5], &objectname, &olen, &event_type, &helflag) == FAILURE) {
       return;
    }
    rc = swe_heliacal_pheno_ut(tjdstart, dgeo, datm, dobs, objectname, (int32)event_type, (int32)helflag, darr, serr);
    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);
    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       for(i = 0; i <= 29 ; i++)
          add_index_double(return_value, i, darr[i]);
    }
}

PHP_FUNCTION(swe_vis_limit_mag)
{
    int rc;
    double tjdstart, dgeo[3], datm[4], dobs[6], darr[8];
    char serr[AS_MAXCH], *objectname = NULL;
    int i;
    size_t olen;
    zend_long helflag;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddddddddddddddsl", &tjdstart, &dgeo[0], &dgeo[1], &dgeo[2], &datm[0], &datm[1], &datm[2], &datm[3], &dobs[0], &dobs[1], &dobs[2], &dobs[3], &dobs[4], &dobs[5], &objectname, &olen, &helflag) == FAILURE) {
       return;
    }
    rc = swe_vis_limit_mag(tjdstart, dgeo, datm, dobs, objectname, (int32)helflag, darr, serr);
    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);
    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       for(i = 0; i < 8 ; i++)
          add_index_double(return_value, i, darr[i]);
    }
}

PHP_FUNCTION(swe_azalt)
{
    zend_long calc_flag;
    double tjd_ut, geopos[3], atpress, attemp, xin[2], xaz[3];
    int i;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlddddddd", &tjd_ut, &calc_flag, &geopos[0], &geopos[1], &geopos[2], &atpress, &attemp, &xin[0], &xin[1]) == FAILURE) {
       return;
    }
    swe_azalt(tjd_ut, (int32)calc_flag, geopos, atpress, attemp, xin, xaz);

    array_init(return_value);
    for(i = 0; i < 3; i++)
       add_index_double(return_value, i, xaz[i]);
}

PHP_FUNCTION(swe_azalt_rev)
{
    zend_long calc_flag;
    double tjd_ut, geopos[3], xin[2], xout[3];
    int i;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlddddd", &tjd_ut, &calc_flag, &geopos[0], &geopos[1], &geopos[2], &xin[0], &xin[1]) == FAILURE) {
       return;
    }
    swe_azalt_rev(tjd_ut, (int32)calc_flag, geopos, xin, xout);

    array_init(return_value);
    for(i = 0; i < 2; i++)
       add_index_double(return_value, i, xout[i]);
}

PHP_FUNCTION(swe_rise_trans)
{
    size_t s_len;
    int rc;
    zend_long ipl, epheflag, rsmi;
    double tjd_ut, geopos[3], tret[10], atpress, attemp;
    char serr[AS_MAXCH], *starname = NULL;
    char star[MAX_FIXSTAR_NAME + 1];
    int i;
    zval tret_arr;
    *serr = '\0';
    *star = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlsllddddd", &tjd_ut, &ipl, &starname, &s_len, &epheflag, &rsmi, &(geopos[0]), &(geopos[1]), &(geopos[2]), &atpress, &attemp) == FAILURE) {
       return;
    }

    if (starname != NULL && s_len > 0) {
        if (s_len > MAX_FIXSTAR_NAME) starname[MAX_FIXSTAR_NAME] = '\0';
       strcpy(star, starname);
    }
    rc = swe_rise_trans(tjd_ut, (int32)ipl, star, (int32)epheflag, (int32)rsmi, &(geopos[0]), atpress, attemp, tret, serr);

    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);

    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 10; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
       if (starname != NULL && s_len > 0)
          add_assoc_string(return_value, "star", star);
    }
}

PHP_FUNCTION(swe_rise_trans_true_hor)
{
    size_t s_len;
    int rc;
    zend_long ipl, epheflag, rsmi;
    double tjd_ut, geopos[3], tret[10], atpress, attemp, horhgt;
    char serr[AS_MAXCH], *starname = NULL;
    char star[MAX_FIXSTAR_NAME + 1];
    int i;
    zval tret_arr;
    *serr = '\0';
    *star = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlslldddddd", &tjd_ut, &ipl, &starname, &s_len, &epheflag, &rsmi, &geopos[0], &geopos[1], &geopos[2], &atpress, &attemp, &horhgt) == FAILURE) {
       return;
    }
    if (starname != NULL && s_len > 0) {
        if (s_len > MAX_FIXSTAR_NAME) starname[MAX_FIXSTAR_NAME] = '\0';
       strcpy(star, starname);
    }
    rc = swe_rise_trans_true_hor(tjd_ut, (int32)ipl, star, (int32)epheflag, (int32)rsmi, geopos, atpress, attemp, horhgt, tret, serr);

    array_init(return_value);
    add_assoc_long(return_value, "rc", rc);

    if (rc == ERR) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&tret_arr);
       for(i = 0; i < 10; i++)
          add_index_double(&tret_arr, i, tret[i]);
       add_assoc_zval(return_value, "tret", &tret_arr);
       if (starname != NULL && s_len > 0)
          add_assoc_string(return_value, "star", star);
    }
}

PHP_FUNCTION(swe_nod_aps)
{
    int rc;
    zend_long ipl, iflag, method;
    double tjd_et, xnasc[6], xndsc[6], xperi[6], xaphe[6];
    char serr[AS_MAXCH];
    int i;
    zval xnasc_arr, xndsc_arr, xperi_arr, xaphe_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlll", &tjd_et, &ipl, &iflag, &method) == FAILURE) {
       return;
    }
    rc = swe_nod_aps(tjd_et, (int32)ipl, (int32)iflag, (int32)method, xnasc, xndsc, xperi, xaphe, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&xnasc_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xnasc_arr, i, xnasc[i]);
       array_init(&xndsc_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xndsc_arr, i, xndsc[i]);
       array_init(&xperi_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xperi_arr, i, xperi[i]);
       array_init(&xaphe_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xaphe_arr, i, xaphe[i]);
       add_assoc_zval(return_value, "xnasc", &xnasc_arr);
       add_assoc_zval(return_value, "xndsc", &xndsc_arr);
       add_assoc_zval(return_value, "xnperi", &xperi_arr);
       add_assoc_zval(return_value, "xnaphe", &xaphe_arr);
    }
}

PHP_FUNCTION(swe_nod_aps_ut)
{
    int rc;
    zend_long ipl, iflag, method;
    double tjd_ut, xnasc[6], xndsc[6], xperi[6], xaphe[6];
    char serr[AS_MAXCH];
    int i;
    zval xnasc_arr, xndsc_arr, xperi_arr, xaphe_arr;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dlll", &tjd_ut, &ipl, &iflag, &method) == FAILURE) {
       return;
    }
    rc = swe_nod_aps_ut(tjd_ut, (int32)ipl, (int32)iflag, (int32)method, xnasc, xndsc, xperi, xaphe, serr);

    array_init(return_value);
    add_assoc_long(return_value, "retflag", rc);

    if (rc < 0) {
       add_assoc_string(return_value, "serr", serr);
    } else {
       array_init(&xnasc_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xnasc_arr, i, xnasc[i]);
       array_init(&xndsc_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xndsc_arr, i, xndsc[i]);
       array_init(&xperi_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xperi_arr, i, xperi[i]);
       array_init(&xaphe_arr);
       for(i = 0; i < 6; i++)
          add_index_double(&xaphe_arr, i, xaphe[i]);
       add_assoc_zval(return_value, "xnasc", &xnasc_arr);
       add_assoc_zval(return_value, "xndsc", &xndsc_arr);
       add_assoc_zval(return_value, "xnperi", &xperi_arr);
       add_assoc_zval(return_value, "xnaphe", &xaphe_arr);
    }
}

PHP_FUNCTION(swe_get_orbital_elements)
{
    int rc;
    zend_long ipl, iflag;
    double tjd_et, dret[50];
    char serr[AS_MAXCH];
    int i;
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dll", &tjd_et, &ipl, &iflag) == FAILURE) {
       return;
    }
    rc = swe_get_orbital_elements(tjd_et, (int)ipl, (int)iflag, dret, serr);

    array_init(return_value);
    for(i = 0; i < 17; i++)
       add_index_double(return_value, i, dret[i]);
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_orbit_max_min_true_distance)
{
    int rc;
    zend_long ipl, iflag;
    double tjd_et, dmax, dmin, dtrue;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dll", &tjd_et, &ipl, &iflag) == FAILURE) {
       return;
    }
    rc = swe_orbit_max_min_true_distance(tjd_et, (int)ipl, (int)iflag, &dmax, &dmin, &dtrue, serr);

    array_init(return_value);
    if (rc >= 0) {
       add_assoc_double(return_value, "dmax", dmax);
       add_assoc_double(return_value, "dmin", dmin);
       add_assoc_double(return_value, "dtrue", dtrue);
    }
    add_assoc_string(return_value, "serr", serr);
    add_assoc_long(return_value, "rc", rc);
}

PHP_FUNCTION(swe_deltat)
{
    double tjd_ut;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &tjd_ut) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_deltat(tjd_ut));
}

PHP_FUNCTION(swe_deltat_ex)
{
    double tjd_ut, dt;
    zend_long ephe_flag;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &tjd_ut, &ephe_flag) == FAILURE) {
       return;
    }

    dt = swe_deltat_ex(tjd_ut, (int32)ephe_flag, serr);

    array_init(return_value);
    add_assoc_double(return_value, "dt", dt);
    add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_time_equ)
{
    double tjd, te;
    int rc;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &tjd) == FAILURE) {
       return;
    }
    rc = swe_time_equ(tjd, &te, serr);
    array_init(return_value);

    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "te", te);
    add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_lmt_to_lat)
{
    double tjd_lmt, geolon;
    double tjd_lat;
    int rc;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &tjd_lmt, &geolon) == FAILURE) {
       return;
    }
    rc = swe_lmt_to_lat(tjd_lmt, geolon, &tjd_lat, serr);
    array_init(return_value);

    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "tjd_lat", tjd_lat);
    add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_lat_to_lmt)
{
    double tjd_lmt, tjd_lat, geolon;
    int rc;
    char serr[AS_MAXCH];
    *serr = '\0';

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &tjd_lat, &geolon) == FAILURE) {
       return;
    }
    rc = swe_lat_to_lmt(tjd_lat, geolon, &tjd_lmt, serr);
    array_init(return_value);

    add_assoc_long(return_value, "rc", rc);
    add_assoc_double(return_value, "tjd_lmt", tjd_lmt);
    add_assoc_string(return_value, "serr", serr);
}

PHP_FUNCTION(swe_sidtime0)
{
    double tjd_ut, eps, nut;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd", &tjd_ut, &eps, &nut) == FAILURE) {
       return;
    }
    RETURN_DOUBLE(swe_sidtime0(tjd_ut, eps, nut));
}

PHP_FUNCTION(swe_sidtime)
{
    double tjd_ut;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &tjd_ut) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_sidtime(tjd_ut));
}

PHP_FUNCTION(swe_cotrans)
{
    int i;
    double xpo[3], xpn[3], eps;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddd", &xpo[0], &xpo[1], &xpo[2], &eps) == FAILURE) {
       return;
    }

    swe_cotrans(xpo, xpn, eps);

    array_init(return_value);
    for(i = 0; i < 3; i++)
       add_index_double(return_value, i, xpn[i]);
}

PHP_FUNCTION(swe_cotrans_sp)
{
    int i;
    double xpo[6], xpn[6], eps;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddddddd", &xpo[0], &xpo[1], &xpo[2], &xpo[3], &xpo[4], &xpo[5], &eps) == FAILURE) {
       return;
    }

    swe_cotrans_sp(xpo, xpn, eps);

    array_init(return_value);
    for(i = 0; i < 6; i++)
       add_index_double(return_value, i, xpn[i]);
}

PHP_FUNCTION(swe_get_tid_acc)
{
    RETURN_DOUBLE(swe_get_tid_acc());
}

PHP_FUNCTION(swe_set_tid_acc)
{
    double t_acc;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &t_acc) == FAILURE) {
       return;
    }
    swe_set_tid_acc(t_acc);
    RETURN_NULL();
}

PHP_FUNCTION(swe_set_delta_t_userdef)
{
    double dt;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &dt) == FAILURE) {
       return;
    }
    swe_set_delta_t_userdef(dt);
    RETURN_NULL();
}

PHP_FUNCTION(swe_degnorm)
{
    double x;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &x) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_degnorm(x));
}

PHP_FUNCTION(swe_radnorm)
{
    double x;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &x) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_radnorm(x));
}

PHP_FUNCTION(swe_rad_midp)
{
    double x1, x0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &x1, &x0) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_rad_midp(x1, x0));
}

PHP_FUNCTION(swe_deg_midp)
{
    double x1, x0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &x1, &x0) == FAILURE) {
       return;
    }

    RETURN_DOUBLE(swe_deg_midp(x1, x0));
}

PHP_FUNCTION(swe_split_deg)
{
    zend_long roundflag;
    double ddeg, dsecfr;
    int32 ideg, imin, isec, isgn;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dl", &ddeg, &roundflag) == FAILURE) {
       return;
    }
    swe_split_deg(ddeg, (int32)roundflag, &ideg, &imin, &isec, &dsecfr, &isgn);
    array_init(return_value);
    add_assoc_long(return_value, "deg", ideg);
    add_assoc_long(return_value, "min", imin);
    add_assoc_long(return_value, "sec", isec);
    add_assoc_double(return_value, "secfr", dsecfr);
    add_assoc_long(return_value, "sgn", isgn);
}

PHP_FUNCTION(swe_csnorm)
{
    zend_long p;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &p) == FAILURE) {
       return;
    }
    RETURN_LONG(swe_csnorm((centisec)p));
}

PHP_FUNCTION(swe_difcsn)
{
    zend_long p1, p2;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &p1, &p2) == FAILURE) {
       return;
    }
    RETURN_LONG(swe_difcsn((centisec)p1, (centisec)p2));
}

PHP_FUNCTION(swe_difdegn)
{
    double p1, p2;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &p1, &p2) == FAILURE) {
       return;
    }
    RETURN_DOUBLE(swe_difdegn(p1, p2));
}

PHP_FUNCTION(swe_difcs2n)
{
    zend_long p1, p2;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &p1, &p2) == FAILURE) {
       return;
    }
    RETURN_LONG(swe_difcs2n((centisec)p1, (centisec)p2));
}

PHP_FUNCTION(swe_difdeg2n)
{
    double p1, p2;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &p1, &p2) == FAILURE) {
       return;
    }
    RETURN_DOUBLE(swe_difdeg2n(p1, p2));
}

PHP_FUNCTION(swe_difrad2n)
{
    double p1, p2;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dd", &p1, &p2) == FAILURE) {
       return;
    }
    RETURN_DOUBLE(swe_difrad2n(p1, p2));
}

PHP_FUNCTION(swe_csroundsec)
{
    zend_long x;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &x) == FAILURE) {
       return;
    }
    RETURN_LONG(swe_csroundsec((centisec)x));
}

PHP_FUNCTION(swe_d2l)
{
    double x;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &x) == FAILURE) {
       return;
    }
    RETURN_LONG(swe_d2l(x));
}

PHP_FUNCTION(swe_day_of_week)
{
    double jd;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &jd) == FAILURE) {
       return;
    }
    RETURN_LONG(swe_day_of_week(jd));
}

PHP_FUNCTION(swe_cs2timestr)
{
    zend_long t, sep, suppressZero;
    char a[AS_MAXCH];

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &t, &sep, &suppressZero) == FAILURE) {
       return;
    }

    RETURN_STRING(swe_cs2timestr((int32)t, (int)sep, (AS_BOOL)suppressZero, a));
}

PHP_FUNCTION(swe_cs2lonlatstr)
{
    zend_long t;
    size_t pchar_len, mchar_len;
    char s[AS_MAXCH], *pchar = NULL, *mchar = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lss", &t, &pchar, &pchar_len, &mchar, &mchar_len) == FAILURE) {
       return;
    }
    if ((pchar_len < 1) || (mchar_len < 1)) return;

    RETURN_STRING(swe_cs2lonlatstr((int32)t, pchar[0], mchar[0], s));
}

PHP_FUNCTION(swe_cs2degstr)
{
    zend_long t;
    char a[AS_MAXCH];

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &t) == FAILURE) {
       return;
    }

    RETURN_STRING(swe_cs2degstr((int32)t, a));
}