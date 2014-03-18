/**
 * GLib - General C++ Library
 * 
 * Copyright (C) 2014 Jozef Stefan Institute
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

namespace TFtrGen {

///////////////////////////////////////
// Numeric-Feature-Generator
class TNumeric {
private:        
	TBool NormalizeP;
    TFlt MnVal;
    TFlt MxVal;

public:
	TNumeric(const bool& _NormalizeP = true):
        NormalizeP(_NormalizeP), MnVal(TFlt::Mx), MxVal(TFlt::Mn) { }
	TNumeric(TSIn& SIn): NormalizeP(SIn), MnVal(SIn), MxVal(SIn) { }
	void Save(TSOut& SOut) const { NormalizeP.Save(SOut); MnVal.Save(SOut); MxVal.Save(SOut); }

    void Update(const double& Val);
	double GetFtr(const double& Val) const;
    void AddFtr(const double& Val, TIntFltKdV& SpV, int& Offset) const;
    void AddFtr(const double& Val, TFltV& FullV, int& Offset) const;
};

///////////////////////////////////////
// Nominal-Feature-Generator
class TNominal {
private:
    TStrH ValH;   

public:
    TNominal() { }
	TNominal(TSIn& SIn): ValH(SIn) { }
	void Save(TSOut& SOut) const { ValH.Save(SOut);}

    void Update(const TStr& Val);
	int GetFtr(const TStr& Val) const { return ValH.IsKey(Val) ? ValH.GetKeyId(Val) : -1; }
    void AddFtr(const TStr& Val, TIntFltKdV& SpV, int& Offset) const;

    int GetVals() const { return ValH.Len(); } 
    TStr GetVal(const int& ValN) const { return ValH.GetKey(ValN); }
};

///////////////////////////////////////
// MultiNomial-Feature-Generator
class TMultiNom {
private:
	TNominal FtrGen;

public:
	TMultiNom() { }
	TMultiNom(TSIn& SIn): FtrGen(SIn) { }
	void Save(TSOut& SOut) const { FtrGen.Save(SOut); }

    void Update(const TStr& Str);
    void Update(const TStrV& StrV);
    void AddFtr(const TStr& Str, TIntFltKdV& SpV, int& Offset) const;
    void AddFtr(const TStrV& StrV, TIntFltKdV& SpV, int& Offset) const;

    int GetVals() const { return FtrGen.GetVals(); } 
	TStr GetVal(const int& ValN) const { return FtrGen.GetVal(ValN); }
};

///////////////////////////////////////
// Tokenizable-Feature-Generator
class TToken {
private:
    PSwSet SwSet;
    PStemmer Stemmer;
    TInt Docs;
    TStrH TokenH;

public:
    TToken(PSwSet _SwSet, PStemmer _Stemmer): SwSet(_SwSet), Stemmer(_Stemmer) { }
	TToken(TSIn& SIn);
	void Save(TSOut& SOut) const;

    void Update(const TStr& Val);
    void AddFtr(const TStr& Val, TIntFltKdV& SpV) const;
    void AddFtr(const TStr& Val, TIntFltKdV& SpV, int& Offset) const;

    int GetVals() const { return TokenH.Len(); } 
    TStr GetVal(const int& ValN) const { return TokenH.GetKey(ValN); }
    void GetTokenV(const TStr& Str, TStrV& TokenStrV) const;

	PSwSet GetSwSet() const { return SwSet; }
	PStemmer GetStemmer() const { return Stemmer; }
};   

///////////////////////////////////////
// Sparse-Feature-Generator
class TSparseNumeric {
private:
    TInt MxId;
	TNumeric FtrGen;

public:
	TSparseNumeric()  { }
	TSparseNumeric(TSIn& SIn): MxId(SIn), FtrGen(SIn) { }
	void Save(TSOut& SOut) const { MxId.Save(SOut); FtrGen.Save(SOut); }

    void Update(const TIntFltKdV& SpV);
    void AddFtr(const TIntFltKdV& InSpV, TIntFltKdV& SpV, int& Offset) const;

    int GetVals() const { return MxId + 1; } 
};

}