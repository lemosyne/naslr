# naslr

Disable ASLR for child processes.

A Rust port of [no-aslr](https://github.com/kccqzy/no-aslr) to provide a safe
function to disable ASLR and `naslr`, an executable that provides the same
functionality as `no-aslr`.

## CLI Usage

```shell
naslr --help
```

## License

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License (a copy of which is present in
this repository), or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
