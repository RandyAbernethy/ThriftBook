#!/usr/bin/env perl

use lib './gen-perl';

use Thrift::Socket;
use Thrift::BufferedTransport;
use Thrift::BinaryProtocol;
use helloSvc;

my $trans_ep    = Thrift::Socket->new("localhost", 9095);
my $trans_buf = Thrift::BufferedTransport->new($trans_ep);
my $proto  = Thrift::BinaryProtocol->new($trans_buf);
my $client    = helloSvcClient->new($proto);

$trans_ep->open;
my $msg = $client->getMessage("World!");
$trans_ep->close;

print $msg."\n"
