#!/usr/bin/env perl

use lib './gen-perl';

use utf8;
use strict;
use warnings;

use Thrift::Socket;
use Thrift::Server;
use helloSvc;

package HelloSvcHandler {
    sub new {
        my ($class, %opts) = @_;
        bless {}, $class;
    }

    sub getMessage {
        my $self = shift;
        my $input = shift;

        return "Hello ".$input;
    }
}

my $trans  = Thrift::ServerSocket->new(9095);
my $proc   = helloSvcProcessor->new(HelloSvcHandler->new);
my $server = Thrift::ForkingServer->new($proc, $trans);

$server->serve;

