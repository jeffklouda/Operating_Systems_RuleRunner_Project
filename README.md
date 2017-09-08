CSE.30341.FA17: Project 01
==========================

This is the documentation for [Project 01] of [CSE.30341.FA17].

[Project 01]:       https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/project01.html
[CSE.30341.FA17]:   https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/

Members
-------

1. Matthew D'Alonzo (mdalonz1@nd.edu)
2. Jeff Klouda (jklouda1@nd.edu)

Design
------

> Explain how you would periodically scan the `root` the directory and detect
> if a file has been created, modified, or removed.
>
>   1. What system calls would you need to use?

>	To do this action, you'd need to use the following system calls: opendir(), readdir(), closedir(), and stat().
>   
>   2. What information would you need to store and what data structures would
>      you need?

>	You would need to store what files are in the directory on the previous scan and the date tag of the files on the previous scan. To keep track of this, you can use a linked list of structs to compare the values of the current scan to the values of the previous scan. 
.

> Explain how you would check if a rule matched an event and execute the
> corresponding action.
>
>   1. What system calls would you need to use?
>	
>   You need to use the following system calls: system().
   
>   2. How would you pass the environment variables to the command?

> Explain how you would handle a [SIGINT] signal and what you would need to
> cleanup?
>
>   1. What system calls would you need to use?
>
>   2. How would you know what resources to cleanup?

Testing
-------

> Describe how you tested and verified that `rorschach` met the project
> requirements.

Analysis
--------

> How is what `rorschach` does similar to how a [system call] operates?

.

> As described in the project requirements, `rorschach` periodically scans the
> `root` directory to detect changes in files.  This process can be described
> as a form of [busy waiting].
>
>   1. In this specific context, why could this be considered a possible
>      negative design flaw?
>
>   2. Consider [inotify(7)] provided by [Linux].  How would these system calls
>      help address the problem of [busy waiting]?
>
>   3. Why might we still consider using [busy waiting] as specified in the
>      original design rather than use something like [inotify(7)]?

[Linux]:        https://kernel.org
[busy waiting]: https://en.wikipedia.org/wiki/Busy_waiting
[system call]:  https://en.wikipedia.org/wiki/System_call
[inotify(7)]:   http://man7.org/linux/man-pages/man7/inotify.7.html

Errata
------

> Describe any known errors, bugs, or deviations from the requirements.

Extra Credit
------------

> Describe what extra credit (if any) that you implemented.
