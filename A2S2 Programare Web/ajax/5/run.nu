#!/usr/bin/env nu

(run-external
  flask
    '--app' app
    run
    '--without-threads' '--port' 5004)
