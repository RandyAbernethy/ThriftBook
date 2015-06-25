const bool b0 = 0		//False		
const bool b1 = 1		//True
const bool b2 = false
const bool b3 = true

const byte i1 = 42      			
const i16 i2 = -42
const i32 i3 = +42
const i64 i4 = 0x4f		//Hex (lower case x only)
const i64 i5 = 0x4F     
const i64 i6 = 042		//Decimal 42(!), no octal support
const i32 i7 = i6		//A const can be initialized with another const 

const double d1 = 123.456			
const double d2 = -123.456
const double d3 = 123.456e6
const double d4 = -123.456E-6 	//Expressions (e.g. 4.5/7.2) not supported
const double d5 = +123.456e+6

const string s1 = "hello"			
const string s2 = 'hello'
const string s3 = "\"Thrift\\hello\tworld\'\r\n"//6 escape sequences 
const binary s4 = 'hello world\n'  			//Binaries are initialized like strings

const list<i16> lc = [ 42, 24, 42 ]	
const set<i32> sc = [ 42, 24, 42 ]			//Duplicates not detected by IDL Compiler
const map<i16,string> mc = { 42:"hello", 24:"world" }

