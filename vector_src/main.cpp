#include <chrono>
#include <iostream>
#include <limits>
#include <vector>
#include "Urho3D/Container/Vector.h"
#include <EASTL/vector.h>

using namespace std;
using namespace std::chrono;
using namespace Urho3D;

// EASTL требует это
// https://github.com/electronicarts/EASTL/blob/master/doc/CMake/EASTL_Project_Integration.md
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}

struct PODStruct
{
    int a;
    int b;
    int c;
};

static_assert(is_trivial<PODStruct>::value && std::is_standard_layout<PODStruct>::value, "");

struct SLStruct
{
    int a;
    int b;
    int* c;

    SLStruct()
        : a(0)
        , b(0)
        , c(nullptr)
    {
    }
};

static_assert(std::is_standard_layout<SLStruct>::value, "");

struct NonPodStruct
{
private:
    int a_;
    int b_;
    int c_;

public:
    NonPodStruct()
        : a_(0)
        , b_(0)
        , c_(0)
    {
    }

    // Конструктор копирования
    NonPodStruct(const NonPodStruct& rhs)
    {
        a_ = rhs.a_;
        b_ = rhs.b_;
        c_ = rhs.c_;
    }

    int a() const { return a_; }
    int b() const { return b_; }
    int c() const { return c_; }

    ~NonPodStruct() {}
};

int main()
{
    // Позволяет выводить UTF-8 в консоль
    setlocale(LC_CTYPE, "en_US.UTF-8");

    const int NUM_ELEMENTS = 20000000;
    const int NUM_REPEATS = 10;
    const int SMALL_NUM_REPEATS = 3;
    const int BIG_NUM_REPEATS = 10000;

    steady_clock::time_point start;
    duration<float> delta;

    // Чтобы оптимизатор не вырезал вектор из исходника
    int ignore_this = 0;

    // ==================================================== PUSH int ====================================================

    // Самый правдивый тест среди всех повторных тестов - минимальный, так как в нем меньше всего шумов
    float min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(i);

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "std::vector<int>::push_back(i) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        PODVector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(i);

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::PODVector<int>::Push(i) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        Vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(i);

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::Vector<int>::Push(i) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------
    
    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        eastl::vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(i);

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "eastl::vector<int>::::push_back(i) " << min_time << "s" << endl;
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== PUSH PODStruct ====================================================

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(PODStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "std::vector<PODStruct>::push_back(PODStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        PODVector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(PODStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::PODVector<PODStruct>::Push(PODStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        Vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(PODStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::Vector<PODStruct>::Push(PODStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------
    
    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        eastl::vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(PODStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "eastl::vector<PODStruct>::push_back(PODStruct()) " << min_time << "s" << endl;
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== PUSH SLStruct ====================================================

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(SLStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "std::vector<SLStruct>::push_back(SLStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        PODVector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(SLStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::PODVector<SLStruct>::Push(SLStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        Vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(SLStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::Vector<SLStruct>::Push(SLStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------
    
    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        eastl::vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(SLStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "eastl::vector<SLStruct>::push_back(SLStruct()) " << min_time << "s" << endl;
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== PUSH NonPodStruct ====================================================

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(NonPodStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "std::vector<NonPodStruct>::push_back(NonPodStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------

    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        Vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(NonPodStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.Size();
    }

    cout << "Urho3D::Vector<NonPodStruct>::Push(NonPodStruct()) " << min_time << "s" << endl;

    // --------------------------------------------------------------------------------------------------------------
    
    min_time = numeric_limits<float>::max();

    for (int r = 0; r < NUM_REPEATS; ++r)
    {
        start = steady_clock::now();

        eastl::vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(NonPodStruct());

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        ignore_this += (int)vec.size();
    }

    cout << "eastl::vector<NonPodStruct>::push_back(NonPodStruct()) " << min_time << "s" << endl;
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== vector<int>[i] ====================================================

    {
        vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i];
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<int>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (int val : vec)
                ignore_this += val;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<int>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        PODVector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i];
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<int>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (int val : vec)
                ignore_this += val;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<int>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i];
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<int>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (int val : vec)
                ignore_this += val;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<int>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (eastl_size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i];
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<int>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (int val : vec)
                ignore_this += val;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<int>::iterator " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== vector<PODStruct>[i] ====================================================

    {
        vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<PODStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (PODStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<PODStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        PODVector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<PODStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (PODStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<PODStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<PODStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (PODStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<PODStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (eastl_size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<PODStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (PODStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<PODStruct>::iterator " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== vector<SLStruct>[i] ====================================================

    {
        vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<SLStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (SLStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<SLStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        PODVector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<SLStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (SLStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<SLStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<SLStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (SLStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<SLStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (eastl_size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i].a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<SLStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (SLStruct& val : vec)
                ignore_this += val.a;
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<SLStruct>::iterator " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== vector<NonPodStruct>[i] ====================================================

    {
        vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(NonPodStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i].a();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<NonPodStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (NonPodStruct& val : vec)
                ignore_this += val.a();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<NonPodStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(NonPodStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (unsigned i = 0; i < vec.Size(); ++i)
                ignore_this += vec[i].a();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<NonPodStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (NonPodStruct& val : vec)
                ignore_this += val.a();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<NonPodStruct>::iterator " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(NonPodStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (eastl_size_t i = 0; i < vec.size(); ++i)
                ignore_this += vec[i].a();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<NonPodStruct>::[i] " << min_time << "s" << endl;

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            for (NonPodStruct& val : vec)
                ignore_this += val.a();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<NonPodStruct>::iterator " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== COPY vector<int> ====================================================

    {
        vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            vector<int> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<int>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        PODVector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            PODVector<int> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<int>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            Vector<int> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<int>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<int> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(i);

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            eastl::vector<int> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<int>::copy " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== COPY vector<PODStruct> ====================================================

    {
        vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            vector<PODStruct> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<PODStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        PODVector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            PODVector<PODStruct> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<PODStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            Vector<PODStruct> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<PODStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<PODStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(PODStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            eastl::vector<PODStruct> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<PODStruct>::copy " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== COPY vector<SLStruct> ====================================================

    {
        vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            vector<SLStruct> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<SLStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        PODVector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            PODVector<SLStruct> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::PODVector<SLStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            Vector<SLStruct> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<SLStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<SLStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(SLStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            eastl::vector<SLStruct> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<SLStruct>::copy " << min_time << "s" << endl;
    }
    
    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== COPY vector<NonPodStruct> ====================================================

    {
        vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(NonPodStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            vector<NonPodStruct> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "std::vector<NonPodStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    {
        Vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.Push(NonPodStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            Vector<NonPodStruct> copy = vec;
            ignore_this += copy.Size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "Urho3D::Vector<NonPodStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------
    
    {
        eastl::vector<NonPodStruct> vec;
        for (int i = 0; i < NUM_ELEMENTS; ++i)
            vec.push_back(NonPodStruct());

        min_time = numeric_limits<float>::max();

        start = steady_clock::now();

        for (int r = 0; r < NUM_REPEATS; ++r)
        {
            eastl::vector<NonPodStruct> copy = vec;
            ignore_this += copy.size();
        }

        delta = steady_clock::now() - start;
        min_time = min(min_time, delta.count());

        cout << "eastl::vector<NonPodStruct>::copy " << min_time << "s" << endl;
    }

    // --------------------------------------------------------------------------------------------------------------

    cout << endl;

    // ==================================================== КОНЕЦ ====================================================

    // Используем переменную, чтобы оптимизатор не выкинул её
    cout << "ignore this " << ignore_this << endl;
    
    //cout << "Press ENTER..." << endl;
    //cin.get();

    return 0;
}
