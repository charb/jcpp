
#include "jcpp/outlook/server/JOutlook.h"
#include "jcpp/lang/JInteger.h"

#include <windows.h>
#include <Mapi.h>

namespace jcpp {
	namespace outlook {
		namespace server{

				static HINSTANCE hMAPI = NULL;
				static LPMAPISENDMAIL lpfnMAPISendMail = NULL;

				JOutlook::JOutlook(JString* tempFolder) : JObject(getClazz()){
					this->tempFolder = tempFolder;
					this->fileCounter = new JInteger(1);
					JOutlook::init();
				}

				void JOutlook::openMailMessageInOutlook(JMailMessage *msg){
					JSystem::out->println(new JString("open mail method called"));

					openMail(
							msg->getToList(),
							msg->getCcList(),
							msg->getBccList(),
							msg->getBody(),
							msg->getSubject(),
							true,
							true);
				}

				void JOutlook::init() {
					hMAPI = ::LoadLibrary("mapi32.dll");
					lpfnMAPISendMail = (LPMAPISENDMAIL)::GetProcAddress(hMAPI, "MAPISendMail");
				}

				char * JOutlook::heapedString(JString * st){
					char * result = new char[st->length() + 1];
					strcpy(result, st->getString().c_str());
					result[st->length()] = 0x00;
					return result;
				}

				void JOutlook::addRecipients(JList *to, jlong type, void *vv, int start){
					MapiRecipDesc * v = (MapiRecipDesc*)vv;

					for (int i = start; i < to->size() + start; ++i){

						JString *name = dynamic_cast<JString*>(to->get(i - start));

						JStringBuilder *strbuilder = new JStringBuilder();
						strbuilder->append(new JString("SMTP:"));
						strbuilder->append(name);

						char * ds = heapedString(name);

						char * ds1 = heapedString(strbuilder->toString());

						memset(&v[i], 0, sizeof(MapiRecipDesc));

						v[i].ulRecipClass = type;
						v[i].lpszAddress = (LPSTR)const_cast<char *>(ds1);
						v[i].lpszName = (LPSTR)const_cast<char *>(ds);
					}
				}

				jbool JOutlook::openMail(JList *to, JList *cc, JList *bcc, JString *text, JString *subject, jbool isHTML, jbool gui)
				{
					if(text == NULL) {
						text = new JString("");
					}
					if(subject == NULL) {
						subject = new JString("");
					}

					JSystem::out->println(new JString("attempting to open outlook"));

					MapiMessage MAPImsg = { 0 };

					int nbRecipients = to->size() + cc->size() + bcc->size();
					MapiRecipDesc* v = new MapiRecipDesc[nbRecipients];



					addRecipients(to, MAPI_TO, v, 0);
					addRecipients(cc, MAPI_CC, v, to->size());
					addRecipients(bcc, MAPI_BCC, v, to->size() + cc->size());

					MAPImsg.nRecipCount = nbRecipients;
					MAPImsg.lpRecips = v;

					MapiFileDesc file = {0};

					JStringBuilder *jfileName = new JStringBuilder();
					jfileName->append(tempFolder);
					jfileName->append(JInteger::toString(fileCounter->get()));
					jfileName->append(new JString("_body.html"));
					fileCounter->set(fileCounter->get()+1);

					char * body = heapedString(text);

					JFile *jfile = new JFile(jfileName->toString());

					char * filename = heapedString(jfile->getAbsolutePath());


					if (isHTML){
						JFileOutputStream *fos = new JFileOutputStream(jfile, false);
						fos->write(text->getBytes());
						fos->close();
						ZeroMemory(&file, sizeof(MapiFileDesc));
						file.lpszFileName = "messageFile.html";
						file.lpszPathName = filename;
						file.nPosition = -1;
						MAPImsg.nFileCount = 1;
						MAPImsg.lpFiles = &file;
					} else {
						MAPImsg.lpszNoteText =  const_cast<char *>(body);
					}

					char * subj = heapedString(subject);
					MAPImsg.lpszSubject = (LPSTR)const_cast<char *>(subj);

					ULONG nSent = 0;

					JSystem::out->println(new JString("launching outlook......"));

					char buffer[1000];
					GetCurrentDirectory(1000, buffer);

					if (gui)
						nSent = lpfnMAPISendMail(0, 0, &MAPImsg, MAPI_LOGON_UI | MAPI_DIALOG, 0);
					else
						nSent = lpfnMAPISendMail(0, 0, &MAPImsg, 0, 0);

					SetCurrentDirectory(buffer);

					JSystem::out->println(new JString("freeing memory......"));
					jfile->deleteFile();
					delete []filename;
					delete []subj;
					delete []body;
					for (int i = 0; i < nbRecipients; ++i){

						if (v[i].lpszAddress != null)
							delete v[i].lpszAddress;

						if (v[i].lpszName != null)
							delete v[i].lpszName;

						if (v[i].lpEntryID != null)
							delete v[i].lpEntryID;

					}
					delete [] v;

					JSystem::out->println(new JString("returning......"));

					return (nSent == SUCCESS_SUCCESS || nSent == MAPI_E_USER_ABORT);
				}

				void JOutlook::setTempFolder(JString* path) {
					this->tempFolder = path;
				}

				JString* JOutlook::getTempFolder() {
					return tempFolder;
				}

				JOutlook::~JOutlook() {
					FreeLibrary(hMAPI);
				}
		}
	}
}


