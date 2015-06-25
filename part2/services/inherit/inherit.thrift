include "simple.thrift"

service SocialUpdate extends simple.SocialLookup {
    oneway void UpdateSiteUsers( 1: string name, 2: i32 users )
    i32 GetSiteUsersByName( 1: string name )
}
