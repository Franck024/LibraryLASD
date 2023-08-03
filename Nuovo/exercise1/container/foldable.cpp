
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

bool AuxFoldExist(const Data& data, const void* val){
    if (data == *((Data*) val))
        return true;
    return false;
}

bool FoldableContainer<Data>::Exists(const Data& data) const noexcept{
    bool exists = false;
    exists = Fold(&AuxFoldExist<Data>, &data);
    return exists;
}

/* ************************************************************************** */

}
