namespace * music		

enum PerfRightsOrg {	
    ASCAP = 1,
    BMI = 2,
    SESAC = 3,
    Other = 4
}

typedef double Minutes	

struct MusicTrack {		
    1: string title,
    2: string artist,
    3: string publisher,
    4: string composer,
    5: Minutes duration,
    6: PerfRightsOrg pro,
}

