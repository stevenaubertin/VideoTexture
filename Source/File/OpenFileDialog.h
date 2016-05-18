//
//  OpenFileDialog.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef OpenFileDialog_h
#define OpenFileDialog_h

#include "../../JuceLibraryCode/JuceHeader.h"

class OpenFileDialog{
    File lastLocation_;
    String filter_;
public:
    class DialogResult{
        Array<File> files_;
    public:
        DialogResult(File f = File::nonexistent){
            files_.add(f);
        }
        DialogResult(File&& f){
            files_.add(std::move(f));
        }
        DialogResult(const Array<File>& files)
            : files_(files){
        }
        DialogResult(Array<File>&& files)
            : files_(std::move(files)){
        }
        virtual bool hasUserCancel()const noexcept{
            return files_.isEmpty();
        }
        const Array<File>& getResults()const noexcept{
            return files_;
        }
        const File getResult()const noexcept{
            return files_[0];
        }
        operator File()const noexcept{
            return getResult();
        }
        operator Array<File>()const noexcept{
            return getResults();
        }
        operator bool()const noexcept{
            return !hasUserCancel();
        }
    };
    struct UserCancel : public DialogResult{
        bool hasUserCancel()const noexcept{
            return true;
        }
        const Array<File>& getResults()const noexcept = delete;
        const File& getResult()const noexcept = delete;
        operator File()const noexcept = delete;
        operator Array<File>()const noexcept = delete;
    };
    
    OpenFileDialog(const File& dir = File::getSpecialLocation(File::userHomeDirectory),
                   const String& filter = String::empty)
        : lastLocation_{dir}, filter_{filter.isEmpty() ? "*.*" : filter}{
    }
    DialogResult openFile(const String& msg = "Choose a file to open..."){
        FileChooser fc (msg, lastLocation_, filter_);
        if (fc.browseForFileToOpen()){
            return DialogResult{lastLocation_ = fc.getResult()};
        }
        return UserCancel{};
    }
    DialogResult openFiles(const String& msg = "Choose files to open..."){
        FileChooser fc (msg, lastLocation_, filter_);
        if (fc.browseForMultipleFilesToOpen()){
            const auto& r = fc.getResults();
            lastLocation_ = r[0];
            return DialogResult{r};
        }
        return UserCancel{};
    }
};

#endif /* OpenFileDialog_h */
