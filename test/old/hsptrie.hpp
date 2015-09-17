/*! \file   hsptrie.hpp

    \brief Defines a tree for containing string keys.

    Contains simple map definition
*/
#include "hptrie.hpp"
#include "hstring.h"
#pragma once

namespace hst
{

template<typename T>
class sptrie: public hst::ptrie<hString,T>
{
  private:
          /*! Clears all data
          */
          void makeClear();
          /*! Jumps to node of specified key, if possible.
              Otherwise returns NULL;
              \param[in] key key value
          */
          typename sptrie::node * jump(const hString & key) const;
  public:
         /*! Constructor
         */
         sptrie();
         /*! Copy constructor
             \param[in] o other sptrie
         */
         sptrie(const sptrie & o);
         /*! Copies a sptrie
             \param[in] o other sptrie
             \return self-reference
         */
         sptrie & operator=(const sptrie & o);
         /*! Destructor
         */
         ~sptrie();
         /*! Adds a new pair to tree
             \param[in] key key
             \param[in] val value
             \return self-reference
         */
         sptrie & add(const hString & key,const  T & val);
         /*! Returns a constant pointer to element, if it exists in ptrie.
             Otherwise returns NULL.
             \param[in] key key
         */
         T const * operator[](const hString & key) const;
         /*! Returns a pointer to element, if it exists in ptrie.
             Otherwise returns NULL.
             \param[in] key key
         */
         T  * operator[](const hString & key) ;
         /*! Removes element from ptrie, if possible
             \param[in] key key of removing element
         */
         sptrie & remove(const hString & key);
         /*! Clears all
         */
         void clear();
};

}

#ifndef HI_STRING_PTRIE
    #define  HI_STRING_PTRIE
    #include "hsptrie_src.hpp"
#endif
