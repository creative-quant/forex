#### FOREX

c++11 forex client for fxcm, which lets you get historical forex data as csv.

This is still in the early stages of development, so use at your own risk!

#### What is next?
- general cleanup
- implement interactive broker client using folly/io/async/AsyncSocket.h
- add fxcm realtime data
- add voltdb-client, and voltdb support
- try and rewrite the fxcm lib

####Dependencies
```
- ForexConnect - http://www.fxcodebase.com/wiki/index.php/Download
- Boost - http://www.boost.org/users/history/version_1_59_0.html
- glog - https://github.com/google/glog
- gflags - https://github.com/gflags/gflags
- folly - https://github.com/facebook/folly/
- wangle - https://github.com/facebook/wangle
```

build
```
autoreconf -i && ./configure && make
````

test
```
make check
```

run
```
./forex --help
    -account (fxcm account type e.g. DEMO or REAL) type: string default: "DEMO"
    -csv (filename for csv output) type: string default: ""
    -from (year/month/date) type: string default: ""
    -password (fxcm password) type: string default: ""
    -symbol (ticker symbol e.g. AUD/USD) type: string default: ""
    -threads (Number of threads. Numbers <= 0 will use the number of cores on
      this machine.) type: int32 default: 0
    -timeframe (t1|m1|m5|m15|m30|H1|H2|H3|H4|H6|H8|D1|W1|M1) type: string
      default: "D1"
    -to (year/month/date) type: string default: ""
    -url (fxcm host url) type: string
      default: "http://www.fxcorporate.com/Hosts.jsp"
    -user (fxcm user name) type: string default: ""
```


