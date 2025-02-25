// === BEGIN  ring.seal.h Name=$Name

extern e3::SealEvalKey * g_pek_$Name;

class $Name
{
        struct Init { Init() { init0(); } } init_object;
        template<typename T> T init(const T & s) { init0(); return s; }

    protected:
        e3::SealNativeCiphertext x;

        static e3::SealEvalKey * pek;
        static const $Name * zero, * unit;

    public:
        static const bool is_signed = false;
        static const int size = 0;
        static const bool is_circuit = false;

        static const char * typname() { return "$Name"; }
        static const char * filname() { return "$Filencname"; }
        static const char * clsname() { return "$Clsencname"; }

        // Constructors
        static void init0()
        {
            if ( !pek )
            {
                initEvalKey(e3::KeyName {typname(), filname()}, pek, g_pek_$Name);
                if ( !unit ) unit = new $Name("$ArithUnit");
                if ( !zero ) zero = new $Name("$ArithZero");
            }
        }

        $Name(): x() {}
        $Name(const char * c) : $Name(std::string(c)) {}
        $Name(e3::SealNativeCiphertext a) : x(a) {}
        $Name(const $Name & a) : x(a.x) {}
        $Name(const std::string & s) : x( pek->decor(s, false), pek->key ) {}

        // public encryption
        explicit $Name(unsigned long long a) : $Name( init(pek)->encrypt( std::to_string(a), 0 ) ) {}
        explicit $Name(const std::vector<unsigned> & a)
            : $Name( init(pek)->encrypt( e3::util::merge( e3::util::extend(a, slots(), 0U), "_" ), 0 ) ) {}
        explicit $Name(const std::vector<unsigned long long> & a)
            : $Name( init(pek)->encrypt( e3::util::merge( e3::util::extend(a, slots(), 0ULL), "_" ), 0 ) ) {}

        // Operators
        $Name & operator=(const $Name & a) { $Name r(a); x = r.x; return *this; }
        $Name & operator+=(const $Name & a);
        $Name & operator-=(const $Name & a);
        $Name & operator*=(const $Name & a);
        $Name operator+(const $Name & a) const;
        $Name operator-(const $Name & a) const;
        $Name operator*(const $Name & a) const;
        $Name & operator++() { return *this += *unit; }
        $Name & operator--() { return *this -= *unit; }
        $Name operator++(int) { $Name r(*this); ++*this; return r; }
        $Name operator--(int) { $Name r(*this); --*this; return r; }
        $Name operator+() const { return *this; }
        $Name operator-() const;

        $Name operator*(unsigned long long u) const { return e3::multiply_by_ull(*this, u, zero); }
        friend $Name operator*(unsigned long long u, const $Name & a) { return a * u; }
        $Name operator*(const std::vector<unsigned long long> & v) const;
        friend $Name operator*(const std::vector<unsigned long long> & v, const $Name & a) { return a * v; }

        $Name operator+(unsigned long long u) const { return *this + (*unit * u); }
        friend $Name operator+(unsigned long long u, const $Name & a) { return a + u; }
        $Name operator+(const std::vector<unsigned long long> & v) const;
        friend $Name operator+(const std::vector<unsigned long long> & v, const $Name & a) { return a + v; }

        $Name operator-(unsigned long long u) const { return *this - (*unit * u); }
        friend $Name operator-(unsigned long long u, const $Name & a) { return -(a - u); }
        $Name operator-(const std::vector<unsigned long long> & v) const;
        friend $Name operator-(const std::vector<unsigned long long> & v, const $Name & a) { return -(a - v); }

        $Name operator<<(unsigned long long u) const { $Name t(*this); t <<= u; return t; }
        $Name & operator<<=(unsigned long long u) { return *this = e3::shiftL_by_ull(*this, u); }

        // Functions
        $Name & rotate_columns();
        $Name & rotate_rows(size_t s);

        static $Name rotate_columns(const $Name & a) { $Name r(a); return r.rotate_columns(); }
        static $Name rotate_rows(const $Name & a, size_t s) { $Name r(a); return r.rotate_rows(s); }

        std::string str() const { return pek->decor(x.str(), true); }
        static size_t slots() { init0(); return pek->slots(); }
};

inline std::ostream & operator<<(std::ostream & os, const $Name & x) { return os << x.str(); }

$PostfixDefines

// === END  ring.seal.h Name=$Name
