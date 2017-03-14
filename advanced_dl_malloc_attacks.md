## [DL_malloc attacks](http://phrack.org/issues/61/6.html)

An exploit to provide the ability to overwrite an almost arbitrary 4 byte value at any location. 



## [Vudo](http://phrack.org/issues/57/8.html)

**Vulnearable function** : do_syslog() in logging.c file of the sudo tarball.

Called by 2 functions: log-auth() and log-error()

do_syslog() splits the logging message into parts, breaking up the line into so that it fills into a single line. Long command line arguments cause sudo to crash during the function.


