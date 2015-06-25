#!/bin/sh
ant
ant runTransExcepPass
ant -Darg0=BlowUp runTransExcepFail
