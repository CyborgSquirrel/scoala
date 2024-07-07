#!/usr/bin/env nu

(run-external
  protoc
    '-I=.'
    '--java_out=../java/app/AppCore/src/main/java'
    '--csharp_out=../csharp/App/AppCore/srv/application/protobuf'
    ./app.proto)
