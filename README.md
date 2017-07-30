# Concurrent C++

This is a just for fun, use at your own risk, port of some of the concurrency utilities from my Ruby gem [Concurrent Ruby](https://github.com/ruby-concurrency/concurrent-ruby). Which, in turn, is inspired by
[Erlang](http://www.erlang.org/doc/reference_manual/processes.html),
[Clojure](http://clojure.org/concurrent_programming),
[Scala](http://akka.io/),
[Haskell](http://www.haskell.org/haskellwiki/Applications_and_libraries/Concurrency_and_parallelism#Concurrent_Haskell),
[F#](http://blogs.msdn.com/b/dsyme/archive/2010/02/15/async-and-parallel-design-patterns-in-f-part-3-agents.aspx),
[C#](http://msdn.microsoft.com/en-us/library/vstudio/hh191443.aspx),
[Java](http://docs.oracle.com/javase/7/docs/api/java/util/concurrent/package-summary.html),
and classic concurrency patterns.

Although I will endeavor to make everything in this library production ready, I make no promises. This is just a fun side project.

## Thread Safety Note

There are only so many guarantees I can make. This is C++ after all, not Haskell. All of these abstractions make strong thread safety guarantees, especailly with respect to data access. But I cannot prevent you from [blowing your whole leg off](http://www.stroustrup.com/bs_faq.html#really-say-that). If you pass shared, raw, unprotected pointers into a "thread safe" abstraction, don't come crying to me when some random thread skips over all my carefully crafted protections and modifies the data directly.

## License and Copyright

Unless otherwise indicated, everything in this repo is free software released under the [MIT License](http://www.opensource.org/licenses/MIT).

I claim no copyright over the code in this repo. I seek no renumeration or attribution. I accept no liability either. This code is free as in beer, free as in speech, and free of any warranties. Do with it what you will, but do so at your own risk.