/************************************************************************
**
**  Copyright (C) 2009  Strahinja Markovic
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#pragma once
#ifndef IMPORTHTML_H
#define IMPORTHTML_H

#include "ImportTXT.h"
#include "../BookManipulation/FolderKeeper.h"


class ImportHTML : public ImportTXT
{

public:

    // Constructor;
    // The parameter is the file to be imported
    ImportHTML( const QString &fullfilepath );

    // Reads and parses the file 
    // and returns the created Book
    virtual QSharedPointer< Book > GetBook();

protected:

    // Returns a style tag created 
    // from the provided path to a CSS file
    QString CreateStyleTag( const QString &fullfilepath ) const;    

    // Resolves custom ENTITY declarations
    QString ResolveCustomEntities( const QString &html_source ) const; 

    // Strips the file specifier on all the href attributes 
    // of anchor tags with filesystem links with fragment identifiers;
    // thus something like <a href="chapter01.html#firstheading" />
    // becomes just <a href="#firstheading" />
    void StripFilesFromAnchors();

    // Searches for meta information in the HTML file
    // and tries to convert it to Dublin Core
    void LoadMetadata();   

private:
    
    // Loads the source code into the Book
    void LoadSource();       

    // Loads the referenced files into the main folder of the book;
    // as the files get a new name, the references are updated 
    QHash< QString, QString > LoadFolderStructure();

    // Loads CSS files from link tags to style tags.
    // Returns a hash with keys being old references (URLs) to resources,
    // and values being the new references to those resources.
    QHash< QString, QString > LoadImages();

    // Loads style files from link tags to style tags
    void LoadStyleFiles();
};

#endif // IMPORTHTML_H

