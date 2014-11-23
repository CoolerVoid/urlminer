URL-Miner
========

URL-Miner - Is a Recursive web crawler to extracting all urls from web pages.
![Alt text](https://github.com/CoolerVoid/urlminer/blob/master/doc/urlminer_logo.png)
Authors: @CoolerVoid, @pl4nkt0n, @slyfunky

In construction...

TODO:

[ X ]  - Validate URL relative path with DFA [X]
[ X ]  - Add URL parse with cast trick [X]
[   ]  - Add url parse with SSE42 
[ X ]  - Create database with SQLite 
[   ]  - Use SQLite with URLs
[   ]  - Create and use database with Redis
[   ]  - Compare Redis with SQLite and choice one
[   ]  - Create Depth counter at URL Paths
  example:
  domain.com/var1/var2/page.html  = Depth 2
  domain.com/var1/page.html = Depth 1
  domain.com/page.html = Depth 0
[  ]  - Add depth counter per recursive function repeater
[  ]  - Create interface with lib mongoose to use HTTPd
[  ]  - Create a web views to lists URLs
[  ]  - create a web views to lists http response sources with highlights
[  ]  - Add function to use white list regex
[  ]  - Add function to use black list regex
[  ]  - Add threads
[  ]  - Add OpenMPI optins
[  ]  - Add SSL/TLS support
[  ]  - Add CACERT load support
[  ]  - Add random UserAgent support
[  ]  - Add random proxy load support
[  ]  - Add support to save session to continues extracting urls other hour...
[  ]  - Add Pause support
[  ]  - add support to save XML
[  ]  - Add support to save sqlite database
