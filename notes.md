Linux stores a lot of system data in the `/proc` directory. Information about the os can be found in `/etc/os-release/`. 

You can find:

- kernel information in `/proc/version`
- memory utilization in `/proc/meminfo`
- process information in `/proc/stat`
- uptime information (total uptime + idle uptime) `/proc/uptime`
- directories with integer names: these correspond to running processes

You can checkout the [proc manpages](https://man7.org/linux/man-pages/man5/proc.5.html) for more details.

The author of `htop` explains on [stackoverflow](https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290) how he uses `meminfo` to calculate the stats you can see in `htop`:

- Total used memory = MemTotal - MemFree
- Non cache/buffer memory (green) = Total used memory - (Buffers + Cached memory)
- Buffers (blue) = Buffers
- Cached memory (yellow) = Cached + SReclaimable - Shmem
- Swap = SwapTotal - SwapFree
