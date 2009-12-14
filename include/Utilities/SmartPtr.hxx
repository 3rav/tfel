/*
 * \file   SmartPtr.hxx
 * \brief  this file describes the implementation of SmartPtr.
 * \author Thomas Helfer
 * \date   december 2005
 */

#ifndef _LIB_TFEL_SMARTPTR_HPP_
#define _LIB_TFEL_SMARTPTR_HPP_

#include<string>
#include<cassert>
#include"Utilities/Name.hxx"

#define TFEL_INLINE inline

namespace tfel{
  
  namespace utilities{

    /*! \class SmartPtr
     *  \brief La classe \c SmartPtr se substitue aux pointeurs
     *  traditionnels auxquels elle ajoute la d�sallocation
     *  automatique de la m�moire.
     *  \author  Helfer Thomas
     *  \date    20 F�vrier 2006
     *  \warning Cette classe ne doit pas �tre utilis�e sur un tableau
     *
     *  La classe \c SmartPtr propose une implantation d'un pointeur
     *  intelligent bas� sur un compteur de r�f�rence. Cette classe
     *  est adapt�e � son utilisation avec les conteneurs de la STL.
     */  
    template<typename T>
    struct SmartPtr{

      typedef T type;

      /*!
       * \brief  Return the name of the class.
       * \param  void.
       * \return const std::string, the name of the class.
       * \see    Name.
       */
      static
      std::string 
      getName(void){
	using namespace std;
	using namespace tfel::utilities;
	return string("tfel::utilities::SmartPtr<")+Name<T>::getName()+string(">");
      }

      /*! \fn SmartPtr::SmartPtr() 
       *  \brief Constructeur par d�faut
       *  
       *  Par d�faut, les membres \c p et \c i sont initialis�s au
       *  pointeur \c 0
       *
       */
      TFEL_INLINE SmartPtr() throw()
	: p(0), i(0) {}
  
      /*! \fn SmartPtr::SmartPtr(T *src) 
       *  \brief Constructeur � partir d'un pointeur
       *  \warning Cette classe ne doit pas �tre utilis�e sur un tableau
       *
       *  La classe \c SmartPtr se charge de d�sallouer la m�moire sur
       *  laquelle pointe le pointeur en argument.
       *
       *  \latexonly
       *  Une utilisation typique de cette m�thode est~:
       *  \begin{center}
       *  SmartPtr<double> p(new double);
       *  \end{center}
       *  \endlatexonly
       *
       *  \param src : pointeur servant � initialiser la classe 
       */
      TFEL_INLINE explicit SmartPtr(T *src)
	: p(src), i(0) {
	if(p!=0){
	  this->i = new unsigned int(1);
	}
      }

      /*! \fn SmartPtr::SmartPtr(const T& src) 
       *  \brief Constructeur � partir d'un objet
       *  \warning Cette classe ne doit pas �tre utilis�e sur un tableau
       *  \warning La classe T doit poss�der un constructeur par copie
       *  La classe \c SmartPtr se charge de d�sallouer la m�moire sur
       *  laquelle pointe le pointeur en argument.
       *
       *  \latexonly
       *  Une utilisation typique de cette m�thode est~:
       *  \begin{center}
       *  SmartPtr<double> p(12.);
       *  \end{center}
       *  \endlatexonly
       *
       *  \param src : pointeur servant � initialiser la classe 
       */
      TFEL_INLINE explicit SmartPtr(const T& src)
	: i(0) {
	this->p = new T(src);
	this->i = new unsigned int(1);
      }

      /*! \fn SmartPtr::SmartPtr(const SmartPtr<T>& src) 
       *  \brief  Constructeur par copie
       *  
       *  \param[in] src \c SmartPtr source utilis� pour initialiser la
       *  classe. 
       */
      TFEL_INLINE SmartPtr(const SmartPtr<T>& src) throw()
	: p(src.p), i(src.i) 
      {
	if(i!=0){
	  ++(*(this->i));
	}
      }

      /*! \fn    SmartPtr::~SmartPtr() 
       *  \brief Destructeur
       *  
       */
      TFEL_INLINE
      ~SmartPtr()  throw()
      {
	this->decreaseCounter();
      }

      /*! \fn      const SmartPtr<T>& operator=(const SmartPtr<T>& src)
       *  \brief  Op�rateur d'affectation
       *  \param[in] src \c SmartPtr source auquel la classe
       *  est affect�.        
       */
      TFEL_INLINE
      SmartPtr<T>&
      operator=(const SmartPtr<T>& src)
	throw()
      {
	// Traitement d'une affectation � soi-m�me
	if(this==&src){
	  return *this;
	}
	if(this->i!=0){
	  this->decreaseCounter();
	}
	this->i=src.i;
	this->p=src.p;
	if(i!=0){
	  *(this->i) += 1;
	}
	return *this;
      }

      /*! \fn     const T& operator*(void) 
       *  \brief  Op�rateur de d�f�rencement (version \c const).
       *  \warning Il est a priori n�cessaire de v�rifier que l'objet r�f�renc� par la classe � bien �t� initialis�.
       *  \return Retourne une r�f�rence constante vers l'objet
       *  contenu par la classe.
       */
      TFEL_INLINE const T& operator*(void) const 
	throw()
      {
	assert(p!=0);
	return *(this->p);
      }

      /*! \fn     const T& operator*(void) 
       *  \brief  Op�rateur de d�f�rencement.
       *  \warning Il est a priori n�cessaire de v�rifier que l'objet r�f�renc� par la classe � bien �t� initialis�.
       *  \return Retourne une r�f�rence vers l'objet contenu par la
       *  classe.
       */
      TFEL_INLINE T& operator*(void) throw()
      {
	assert(p!=0);
	return *(this->p);
      }

      /*! \fn const T* operator->(void) 
       *  \brief  Op�rateur de d'indirection (version constante).
       *  \warning Il est a priori n�cessaire de v�rifier que l'objet r�f�renc� par la classe � bien �t� initialis�.
       *  \return Retourne un pointeur vers l'objet contenu par la
       *  classe. L'objet point� ne peut �tre modifi�.
       */
      TFEL_INLINE
      const T*
      operator->(void) const throw()
      {
	assert(p!=0);
	return this->p;
      }
      
      /*! 
       *  \brief  Op�rateur de d'indirection.
       *  \warning Il est a priori n�cessaire de v�rifier que l'objet r�f�renc� par la classe � bien �t� initialis�.
       *  \return Retourne un pointeur vers l'objet contenu par la
       *  classe. L'objet point� ne peut �tre modifi�.
       */
      TFEL_INLINE
      T* operator->(void) throw()
      {
	assert(p!=0);
	return this->p;
      }
      
      /*! 
       *  \brief   Permet de savoir si la classe pointe sur un objet valide
       *  \return \c true si la classe pointe sur un objet valide, \c false sinon.
       */
      TFEL_INLINE
      bool
      isValid(void) const throw()
      {
	return !(this->p==0);
      }

      /*! \fn      unsigned int count(void)
       *  \brief   Permet de conna�tre le nombre de r�f�r�nces sur
       *           l'objet r�f�renc� par la classe.
       *  \warning Cette m�thode n'est fournie que pour le d�bogage~:
       *           elle est d�sactiv�e si le symbole NDEBUG est d�fini.  
       *  \return  Le nombre de r�f�rences
       */
      TFEL_INLINE
      unsigned int
      count(void) const throw()
      {
	if(i!=0){
	  return *(this->i);
	}
	return 0;
      }

      /*! \fn    void makeUniq(void)
       *  \brief R�alise un copie de l'objet r�f�renc� et pointe dessus 
       */
      TFEL_INLINE
      void makeUniq(void){
	if(this->i!=0){
	  if(*(this->i)!=1){
	    --(*(this->i));
	    this->p = new T(*(this->p));
	    this->i = new unsigned int(1);
	  }
	}
      }

      /*! \fn T* getPtr(void)
       */
      TFEL_INLINE T * getPtr(void){
	return this->p;
      }
      
      /*! \fn T* getPtr(void) const
       */
      TFEL_INLINE
      const T *
      getPtr(void) const{
	return this->p;
      }

    protected:

      T *p;
      
    private:

      mutable unsigned int *i; 
     
      /*! \fn SmartPtr::decreaseCounter() 
       *  \brief   m�thode charg�e de d�cr�menter le compteur de r�f�rence
       *  
       *  Cette m�thode est charg�e de d�cr�menter le compteur de
       *  r�f�rence \c i et de d�sallouer la m�moire si celui-ci est nul.
       */
      TFEL_INLINE void decreaseCounter(void) throw() {
	if(this->i!=0){
	  if((--*(this->i))==0){
	    delete i;
	    delete p;
	    i=0;
	    p=0;
	  }
	}
      }

    };

    template<typename T>
    struct PtrType
    {
      typedef SmartPtr<T> type;
    }; // end of struct PtrType

  } // end of namespace utilities

} // end of namespace tfel

#endif	    /* !SMARTPTR_HPP_ */
