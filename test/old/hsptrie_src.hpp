
namespace hst
{
    template<class T> sptrie<T>::sptrie()  { this->m_root=NULL; }
    template<class T> sptrie<T>::~sptrie() { makeClear(); }
    template<class T> void sptrie<T>::makeClear() { this->m_list.clear();if (this->m_root) delete this->m_root; this->m_root=NULL; }
    template<class T> void sptrie<T>::clear() {makeClear();}
    template<class T> sptrie<T>::sptrie(const sptrie<T> & o )
    {
        this->m_root=NULL;

        typename sptrie::const_iterator it;
        for (it=o.const_begin;it.dereferencable();++it)
           this->add(it.key(),it.value());
    }
    template<class T> sptrie<T> & sptrie<T>::operator=(const sptrie<T> & o )
    {
        this->makeClear();

        typename sptrie::const_iterator it;
        for (it=o.const_begin;it.dereferencable();++it)
           this->add(it.key(),it.value());

        return *this;
    }
    template<class T> sptrie<T> & sptrie<T>::add(const hString & key, const T & val)
    {
      if (!this->m_root) this->m_root=new  typename sptrie<T>::node();
      typename sptrie<T>::node * cur=this->m_root;
      long sz=key.length();
      long i=0;
      for (i=0;i<sz;i++)
      {
          typename sptrie<T>::node ** tmp=&((cur->getChildren((unsigned char)(key[i]))));
          //printf("Iteration: %d Byte: %d  &&: %p &: %p\n",i,bytes[i],tmp,*tmp);
          if (!(*tmp))
             *tmp=new typename sptrie<T>::node();
          cur=*tmp;
      }

      //printf("Started adding: \n");
      //Adding  to list and setting iterator
      if (!cur->m_val.works())
      {
       this->m_list<<triplet<hString,T,void*>(key,val,NULL);
       typename hst::deque< hst::triplet<hString,T, void *> >::iterator last=this->m_list.end(); --last;
       cur->m_val=last;
       (*last).set3((void*)&(cur->m_val));
      }
      else
      {
         (*(cur->m_val)).set2(val);
      }
      //printf("Setting iterator: \n");
      //Setting pointer to iterator
      return *this;
     }

     template<typename T>
     typename sptrie<T>::node * sptrie<T>::jump(const hString & key) const
     {
        typename sptrie::node * cur=this->m_root;
        size_t sz=key.length();
        size_t i=0;
        for (i=0;(i<sz) && (cur);i++)
        {
          cur=cur->getChildren((unsigned char)key[i]);
        }
        return cur;
     }

     template<typename T> T const * sptrie<T>::operator[](const hString & key) const
     {
       typename sptrie<T>::node * cur=jump(key);
       if (!cur) return NULL;
       if (!(cur->m_val.works())) return NULL;
       return &(  (*(cur->m_val)).p2() );
     }
     template<typename T> T  * sptrie<T>::operator[](const hString & key)
     {
       typename sptrie<T>::node * cur=jump(key);
       if (!cur) return NULL;
       if (!(cur->m_val.works())) return NULL;
       return &(  (*(cur->m_val))._2() );
     }
     template<typename T> sptrie<T> & sptrie<T>::remove(const hString  & key)
     {
      typename sptrie<T>::node * cur=jump(key);
      if (!cur) return *this;
      if (!(cur->m_val.works())) return *this;
      (cur->m_val.erase())=typename hst::deque<hst::triplet<hString,T,void *> >::iterator();
      return *this;
     }
}
