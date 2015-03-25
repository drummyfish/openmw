
#include "searchbox.hpp"

#include <stdexcept>

#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>

#include "../../model/world/columns.hpp"

#include "../../model/tools/search.hpp"

void CSVTools::SearchBox::updateSearchButton()
{
    if (!mSearchEnabled)
        mSearch.setEnabled (false);
    else
    {
        switch (mMode.currentIndex())
        {
            case 0:
            case 1:
            case 2:
            case 3:

                mSearch.setEnabled (!mText.text().isEmpty());
                break;

            case 4:

                mSearch.setEnabled (true);
                break;
        }
    }
}

CSVTools::SearchBox::SearchBox (QWidget *parent)
: QWidget (parent), mSearch ("Search"), mSearchEnabled (false)
{
    std::vector<std::string> states =
        CSMWorld::Columns::getEnums (CSMWorld::Columns::ColumnId_Modification);
    states.resize (states.size()-1); // ignore erased state

    for (std::vector<std::string>::const_iterator iter (states.begin()); iter!=states.end();
        ++iter)
        mRecordState.addItem (QString::fromUtf8 (iter->c_str()));
        
    mLayout = new QGridLayout (this);

    mMode.addItem ("Text");
    mMode.addItem ("Text (RegEx)");
    mMode.addItem ("Reference");
    mMode.addItem ("Reference (RegEx)");
    mMode.addItem ("Record State");

    mLayout->addWidget (&mMode, 0, 0);

    mLayout->addWidget (&mSearch, 0, 3);

    mInput.insertWidget (0, &mText);
    mInput.insertWidget (1, &mRecordState);

    mLayout->addWidget (&mInput, 0, 1);
    
    mLayout->setColumnMinimumWidth (2, 50);
    mLayout->setColumnStretch (1, 1);

    mLayout->setContentsMargins (0, 0, 0, 0);
    
    connect (&mMode, SIGNAL (activated (int)), this, SLOT (modeSelected (int)));

    connect (&mText, SIGNAL (textChanged (const QString&)),
        this, SLOT (textChanged (const QString&)));

    connect (&mSearch, SIGNAL (clicked (bool)), this, SLOT (startSearch (bool)));
        
    modeSelected (0);

    updateSearchButton();
}

void CSVTools::SearchBox::setSearchMode (bool enabled)
{
    mSearchEnabled = enabled;
    updateSearchButton();
}

CSMTools::Search CSVTools::SearchBox::getSearch() const
{
    CSMTools::Search::Type type = static_cast<CSMTools::Search::Type> (mMode.currentIndex());
    
    switch (type)
    {
        case CSMTools::Search::Type_Text:
        case CSMTools::Search::Type_Reference:

            return CSMTools::Search (type, std::string (mText.text().toUtf8().data()));
        
        case CSMTools::Search::Type_TextRegEx:
        case CSMTools::Search::Type_ReferenceRegEx:

            return CSMTools::Search (type, QRegExp (mText.text().toUtf8().data(), Qt::CaseInsensitive));
        
        case CSMTools::Search::Type_RecordState:

            return CSMTools::Search (type, mRecordState.currentIndex());

        case CSMTools::Search::Type_None:

            break;
    }

    throw std::logic_error ("invalid search mode index");
}

void CSVTools::SearchBox::modeSelected (int index)
{
    switch (index)
    {
        case CSMTools::Search::Type_Text:
        case CSMTools::Search::Type_TextRegEx:
        case CSMTools::Search::Type_Reference:
        case CSMTools::Search::Type_ReferenceRegEx:

            mInput.setCurrentIndex (0);
            break;

        case CSMTools::Search::Type_RecordState:
            mInput.setCurrentIndex (1);
            break;
    }

    updateSearchButton();
}

void CSVTools::SearchBox::textChanged (const QString& text)
{
    updateSearchButton();
}

void CSVTools::SearchBox::startSearch (bool checked)
{
    emit startSearch (getSearch());
}
