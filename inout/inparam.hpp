/*! \file inparam.hpp
 *
 * \brief Definition of input parameters
 *
 * \version 1.0
 * \date 2015-2017
 * \authors Hermes Robles-Berumen <hermes@uaz.edu.mx>\n Sebastian Ventura <sventura@uco.es>\n Amelia Zafra <azafra@uco.es>\n <a href="http://www.uco.es/kdis/">KDIS</a>
 * \copyright <a href="https://www.gnu.org/licenses/gpl-3.0.en.html">GPLv3</a> license
 */
 
#ifndef IN_PARAM_HPP
#define IN_PARAM_HPP

#include <cstddef>
#include <time.h>
#include "inparam_readinst.hpp"
#include "outfilename.hpp"


/*! \namespace inout
  \brief Module for input and output parameters
  \details
  
  \version 1.0
  \date   2015-2017
  \copyright GPLv3 license
*/

namespace  inout {
  
typedef enum {LABEL, CENTROIDS, CRISPPARTITION, MEDOIDS, DENSITY_BASED,HIERARCHICAL,OTHER} InParam_algTypeOut;


/*! \class InParamAlgorithmo
  \brief Input parameter for define propertys of the algorithmos
*/
class InParamAlgorithmo: public InParamReadInst {
public:
  InParamAlgorithmo
  (std::string        ais_algorithmoName, 
   std::string        ais_algorithmoAuthor, 
   InParam_algTypeOut aiato_algTypeOut
   ):
    InParamReadInst(),
    s_algorithmoName(ais_algorithmoName), 
    s_algorithmoAuthor(ais_algorithmoAuthor), 
    ato_algTypeOut(aiato_algTypeOut),
 
    ps_fileNameTimesRun(NULL),
    b_progressBarPrinting(false),
    i_timesRunAlgorithm(1),
    s_gnuplotCoreStyles("linespoints")
 
  {
    time_t     ltt_runTime       = time(NULL);
    struct tm  *ltm_localrunTime = localtime(&ltt_runTime);
    char       ls_runTimeId[INPARAM_SIZE_STRING_ID_TIME];

    sprintf(ls_runTimeId,
	    "%04d%02d%02d:%02d%02d%02d",
	    ltm_localrunTime->tm_year+1900,
	    ltm_localrunTime->tm_mon+1,
	    ltm_localrunTime->tm_mday,
	    ltm_localrunTime->tm_hour,
	    ltm_localrunTime->tm_min,
	    ltm_localrunTime->tm_sec
	    );
    _s_runTimeId.assign(ls_runTimeId);
  }

  ~InParamAlgorithmo() {}

  void errorArgument(char *apc_command, const char *apc_options, const char *aas_arguments[]);

  bool isYesNo(char  *optarg, char *apc_command, const char *apc_options);
  
  inline void setFileNameTimesRun(char *aips_nameFile) 
  {
    this->ps_fileNameTimesRun = aips_nameFile;
  }


  inline void setProgressBarPrinting(bool aib_bool)   
  {
    this->b_progressBarPrinting = aib_bool;
  }

  inline void setTimesRunAlgorithm(int aii_timesRun)
  {
    this->i_timesRunAlgorithm = aii_timesRun;
  }

  inline void setGnuPlotCoreStyles(const char* aips_nameCoreStyle)
  {
    this->s_gnuplotCoreStyles.assign(aips_nameCoreStyle);
  }

  inline std::string getAlgorithmoAuthor() const
  { 
    return this->s_algorithmoAuthor; 
  }

  inline std::string getAlgorithmoName() const
  { 
    return this->s_algorithmoName; 
  }

  inline char* getFileNameTimesRun() const
  { 
    return this->ps_fileNameTimesRun; 
  }


  inline int getTimesRunAlgorithm() const
  { 
    return this->i_timesRunAlgorithm; 
  }

  inline bool getProgressBarPrinting()
  {
    return this->b_progressBarPrinting;
  }

  inline const std::string getGnuPlotCoreStyles() const
  { 
    return this->s_gnuplotCoreStyles; 
  }

  inline InParam_algTypeOut getAlgorithTypeOut()
  { 
    return this->ato_algTypeOut; 
  }

  inline const std::string& getRunningTimeId()
  {
    return this->_s_runTimeId;
  }

  virtual void print(std::ostream&  aipf_outFile=std::cout, const char aic_separator=',') const
  {
    const char  *larray_opFormatFile[] = INPARAMCLUSTERING_FORMATINSTANCEFILE;
  
    aipf_outFile << "_algorithmo" 
		 << aic_separator << this->s_algorithmoName;
    aipf_outFile << aic_separator << "_author" 
		 << aic_separator << this->s_algorithmoAuthor;
    aipf_outFile << aic_separator << "_dataset" 
		 << aic_separator << this->getCurrentFileInstance();
    aipf_outFile << aic_separator << "_n" 
		 << aic_separator << this->getNumInstances();
    aipf_outFile << aic_separator << "_d" 
		 << aic_separator << this->getNumDimensionsInstances();
    
    if ( this->_vectorstr_filesInstanceTest.size() > 0 ) {
      aipf_outFile << aic_separator << ":dataset test" 
		   << aic_separator << this->getCurrentFileInstanceTest();
      aipf_outFile << aic_separator << ":n" 
		   << aic_separator << this->getNumInstancesTest();
    }
    aipf_outFile << aic_separator << "_format file" 
		 << aic_separator << larray_opFormatFile[this->_enum_formatInstanceFile];
    
    aipf_outFile << aic_separator << "_times run" 
		 << aic_separator << this->i_timesRunAlgorithm
		 << aic_separator << "_runnig date"
		 << aic_separator << this->_s_runTimeId;
  }

  
  friend std::ostream& operator<<(std::ostream& os, const InParamAlgorithmo  &aiinparamalg_inParam)
  {
    aiinparamalg_inParam.print(os);
    
    return os;
  }

protected:

  std::string        s_algorithmoName;
  std::string        s_algorithmoAuthor;
  InParam_algTypeOut ato_algTypeOut;
   
  char               *ps_fileNameTimesRun;
  bool               b_progressBarPrinting;
  int                i_timesRunAlgorithm;
  std::string        _s_runTimeId;
  std::string        s_gnuplotCoreStyles;
  
}; /* InParamAlgorithmo */

} /*END namespace inout 
   */

#endif /*IN_PARAM_HPP*/
