// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef SELECTIONLIST_H
#define SELECTIONLIST_H
#include <state_exports.h>
#include <AttributeSubject.h>

class SelectionProperties;
class SelectionSummary;

// ****************************************************************************
// Class: SelectionList
//
// Purpose:
//    Contains a list of SelectionProperties objects.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

class STATE_API SelectionList : public AttributeSubject
{
public:
    // These constructors are for objects of this class
    SelectionList();
    SelectionList(const SelectionList &obj);
protected:
    // These constructors are for objects derived from this class
    SelectionList(private_tmfs_t tmfs);
    SelectionList(const SelectionList &obj, private_tmfs_t tmfs);
public:
    virtual ~SelectionList();

    virtual SelectionList& operator = (const SelectionList &obj);
    virtual bool operator == (const SelectionList &obj) const;
    virtual bool operator != (const SelectionList &obj) const;
private:
    void Init();
    void Copy(const SelectionList &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectSelections();
    void SelectSelectionSummary();

    // Property setting methods
    void SetAutoApplyUpdates(bool autoApplyUpdates_);

    // Property getting methods
    bool GetAutoApplyUpdates() const;
    const AttributeGroupVector &GetSelections() const;
          AttributeGroupVector &GetSelections();
    const AttributeGroupVector &GetSelectionSummary() const;
          AttributeGroupVector &GetSelectionSummary();

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Attributegroup convenience methods
    void AddSelections(const SelectionProperties &);
    void ClearSelections();
    void RemoveSelections(int i);
    int  GetNumSelections() const;
    SelectionProperties &GetSelections(int i);
    const SelectionProperties &GetSelections(int i) const;

    void AddSelectionSummary(const SelectionSummary &);
    void ClearSelectionSummarys();
    void RemoveSelectionSummary(int i);
    int  GetNumSelectionSummarys() const;
    SelectionSummary &GetSelectionSummary(int i);
    const SelectionSummary &GetSelectionSummary(int i) const;


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    int GetSelection(const std::string &name) const;
    int GetSelectionSummary(const std::string &name) const;

    // IDs that can be used to identify fields in case statements
    enum {
        ID_autoApplyUpdates = 0,
        ID_selections,
        ID_selectionSummary,
        ID__LAST
    };

protected:
    AttributeGroup *CreateSubAttributeGroup(int index);
private:
    bool                 autoApplyUpdates;
    AttributeGroupVector selections;
    AttributeGroupVector selectionSummary;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define SELECTIONLIST_TMFS "ba*a*"

#endif
