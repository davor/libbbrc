// fminer.h
// Andreas Maunz, andreas@maunz.de, oct 2008
#ifndef FMINER_H
#define FMINER_H

#include "misc.h"
#include "closeleg.h"
#include "graphstate.h"

extern bool adjust_ub;
extern bool do_pruning;
extern bool aromatic;
extern ChisqConstraint* chisq;
extern bool do_yaml;
extern bool gsp_out;
extern bool bbrc_sep;

class Fminer {

  public:

    //! Constructor for standard settings: 95% significance level, minimum frequency 2, type trees, dynamic upper bound, BBRC.
    Fminer ();
    //! Like standard constructor, but type and minimum frequency configurable.
    Fminer (int _type, unsigned int _minfreq);
    //! Like standard constructor, but type, minimum frequency, significance level and BBRC configurable.
    Fminer (int _type, unsigned int _minfreq, float chisq_val, bool _do_backbone);

    ~Fminer();
    
    void ReadGsp(FILE* gsp); //!< Read in a gSpan file
    bool AddCompound(string smiles, unsigned int comp_id); //!< Add a compound to the database.
    bool AddActivity(bool act, unsigned int comp_id); //!< Add an activity to the database.
    int GetNoRootNodes() {return database->nodelabels.size();} //!< Get no of root node (element type).
    int GetNoCompounds() {return database->trees.size();}
    vector<string>* MineRoot(unsigned int j); //!< Mine fragments rooted at the j-th root node (element type).

    bool GetConsoleOut(); //!< Get output to console
    bool GetBbrcSep(); //!< Get BBRC separator
    int GetType(); //!< Get type.
    int GetMinfreq(); //!< Get minimum frequency.
    bool GetChisqSig(); //!< Get significance threshold here.

    void SetType(int _type); //!< Set type 1 (paths) or 2 (trees) here.
    void SetMinfreq(int _minfreq); //!< Set minimum frequency (>=1 here).
    void SetChisqSig(float _chisq_val); //!< Set significance threshold here (between 0 and 1).
    void SetChisqActive(bool _val); //!< Specifiy whether Chisq constraint should be used.
    
    bool GetBackbone(); //! Get whether BBRC representatives should be mined.
    bool GetDynamicUpperBound(); //!< Get whether dynamic upper bound pruning is used.
    bool GetPruning(); //!< Get whether statistical metrical pruning is used.
    bool GetAromatic(); //!< Get whether aromatic rings should be perceived instead of Kekule notation.
    bool GetRefineSingles(); //!< Get whether fragments with frequency 1 should be refined.
    bool GetDoOutput(); //!< Get whether output is enabled.

    void SetBackbone(bool val); //!< Pass 'false' here to switch off mining for BBRC representatives.
    void SetDynamicUpperBound(bool val); //!< Pass 'false' here to disable dynamic upper bound pruning (e.g. for performance measures).
    void SetPruning(bool val); //!< Pass 'false' here to disable statistical metrical pruning completely.
    void SetAromatic(bool val); //!< Pass 'false' here to disable aromatic rings and use Kekule notation
    void SetRefineSingles(bool val); //!< Pass 'true' here to enable refinement of fragments with frequency 1.
    void SetDoOutput(bool val); //!< Pass 'false' here to disable output.

    void Reset(); //!< Use this to clear the database before feeding new compounds and activities.
    void Defaults(); //!< Use this to set default parameters as in default constructor.
    void SetConsoleOut(bool val); //!< Set this to true to disable usage of result vector and directly print each fragment to the console (saves memory).
    void SetBbrcSep(bool val); //!< Set this to true to enable BBRC separators in output.
    
  private:
    void AddChiSqNa(){chisq->na++;chisq->n++;}
    void AddChiSqNi(){chisq->ni++;chisq->n++;}

    bool init_mining_done;
    int comp_runner;
    int comp_no;

    vector<string> r;

};

#endif
