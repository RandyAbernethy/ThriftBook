//Radio Telescope Observation Interface
//////////////////////////////////////////////////////////
namespace * radio_observation
const string Version = "1.0.0"

//Mutiple position types are used by the telescopes supported
struct EarthRelPosition {
    1: double latitude
    2: double longitude
    3: double elevation
}
struct RelVector {
    1: EarthRelPosition pos
    2: double declination
    3: double azimuth
}
struct ICRFPosition {
    1: double right_ascension
    2: double declination
    3: optional i16 ecliptic_year
}

/** 
 * The focal point of an observation. May be described by
 * one of several underlying types.
 */
union Position {
    1: EarthRelPosition erpos
    2: RelVector rv
    3: ICRFPosition icrfpos
}

/** 
 * Time in seconds and fractions of seconds since Jan 1, 1970.
 */
typedef double Time

/** 
 * Radio Telescopes and arrays making observations.
 */
enum RadioObservationSystem {
    Parkes  = 1
    Arecibo = 2
    GMRT    = 17
    LOFAR   = 18
    Socorro = 25
    VLBA    = 51
}

/** 
 * An observation made by a radio telescope.
 */
struct RadioObservation {
    1: i32 telescope_count
    2: Time time
    //3: string Researcher; retired
    4: RadioObservationSystem system
    5: map<i64,double> freq_amp
    6: Position pos
    7: optional binary sky_bmp
}

