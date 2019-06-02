#ifndef IOS_BASE_HPP
#define IOS_BASE_HPP

#include <iomanip>

namespace DSAA {
    using streamsize = std::ptrdiff_t;

    class ios_base {
      public:
        class failure;

        using fmtflags = unsigned int;
        static const fmtflags boolalpha = 0x0001;
        static const fmtflags dec = 0x0002;
        static const fmtflags fixed = 0x0004;
        static const fmtflags hex = 0x0008;
        static const fmtflags internal = 0x0010;
        static const fmtflags left = 0x0020;
        static const fmtflags oct = 0x0040;
        static const fmtflags right = 0x0080;
        static const fmtflags scientific = 0x0100;
        static const fmtflags showbase = 0x0200;
        static const fmtflags showpoint = 0x0400;
        static const fmtflags showpos = 0x0800;
        static const fmtflags skipws = 0x1000;
        static const fmtflags unitbuf = 0x2000;
        static const fmtflags uppercase = 0x4000;
        static const fmtflags adjustfield = left | right | internal;
        static const fmtflags basefield = dec | oct | hex;
        static const fmtflags floatfield = scientific | fixed;

        typedef unsigned int iostate;
        static const iostate badbit = 0x1;
        static const iostate eofbit = 0x2;
        static const iostate failbit = 0x4;
        static const iostate goodbit = 0x0;

        typedef unsigned int openmode;
        static const openmode app = 0x01;
        static const openmode ate = 0x02;
        static const openmode binary = 0x04;
        static const openmode in = 0x08;
        static const openmode out = 0x10;
        static const openmode trunc = 0x20;

        enum seekdir { beg = 0, cur = 1, end = 2 };

        class Init;

        fmtflags flags() const;
        fmtflags flags(fmtflags fmtfl);
        fmtflags setf(fmtflags fmtfl);
        fmtflags setf(fmtflags fmtfl, fmtflags mask);
        void unsetf(fmtflags mask);

        streamsize precision() const;
        streamsize precision(streamsize prec);
        streamsize width() const;
        streamsize width(streamsize wide);
    };
}  // namespace DSAA

#endif  // IOS_BASE_HPP
