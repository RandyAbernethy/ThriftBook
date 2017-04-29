exception badMsg {
    1: i16    errorCode
    2: string msg
}

service helloError {
	string getMessage(1: string name)
	  throws (1: badMsg bm)
}

