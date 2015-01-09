#include "jcpp/xml/internal/util/JXmlChars.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JCharacter.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace util{
                
                jbool JXmlChars::isChar(jint ucs4char){
                    return ((ucs4char >= 0x0020 && ucs4char <= 0xD7FF)
                            || ucs4char == 0x000A || ucs4char == 0x0009
                            || ucs4char == 0x000D
                            || (ucs4char >= 0xE000 && ucs4char <= 0xFFFD)
                            || (ucs4char >= 0x10000 && ucs4char <= 0x10ffff));
                }

                jbool JXmlChars::isNameChar(jchar c){
                    if (isLetter2 (c)){
                        return true;
                    
                    }else if (c == '>'){
                        return false;
                    
                    }else if (c == '.' || c == '-' || c == '_' || c == ':' || isExtender (c)){
                        return true;
                    
                    }else{
                        return false;
                    }
                }

                jbool JXmlChars::isNCNameChar(jchar c){
                    return c != ':' && isNameChar (c);
                }

                jbool JXmlChars::isSpace(jchar c){
                    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
                }

                jbool JXmlChars::isLetter(jchar c){
                    if (c >= 'a' && c <= 'z'){
                        return true;
                    }
                    if (c == '/'){
                        return false;
                    }
                    if (c >= 'A' && c <= 'Z'){
                        return true;
                    }
                    return false;

                    //TODO
                    // switch (JCharacter::getType(c)) {
                    //     case JCharacter::LOWERCASE_LETTER:      // Ll
                    //     case JCharacter::UPPERCASE_LETTER:      // Lu
                    //     case JCharacter::OTHER_LETTER:          // Lo
                    //     case JCharacter::TITLECASE_LETTER:      // Lt
                    //     case JCharacter::LETTER_NUMBER:         // Nl
                    //         return !isCompatibilityChar (c) && !(c >= 0x20dd && c <= 0x20e0);

                    //     default:
                    //         return ((c >= 0x02bb && c <=  0x02c1) || c == 0x0559 || c == 0x06e5 || c == 0x06e6);
                    // }
                }

                jbool JXmlChars::isCompatibilityChar(jchar c){
                    switch ((c >> 8) & 0x0ff) {
                        case 0x00:
                            return c == 0x00aa || c == 0x00b5 || c == 0x00ba;

                        case 0x01:
                            return (c >= 0x0132 && c <= 0x0133)
                            || (c >= 0x013f && c <= 0x0140)
                            || c == 0x0149
                            || c == 0x017f
                            || (c >= 0x01c4 && c <= 0x01cc)
                            || (c >= 0x01f1 && c <= 0x01f3) ;

                        case 0x02:
                            return (c >= 0x02b0 && c <= 0x02b8)
                            || (c >= 0x02e0 && c <= 0x02e4);
                      
                        case 0x03:
                            return c == 0x037a;

                        case 0x05:
                            return c == 0x0587;

                        case 0x0e:
                            return c >= 0x0edc && c <= 0x0edd;  // Laotian

                        case 0x11:
                            return c == 0x1101
                            || c == 0x1104
                            || c == 0x1108
                            || c == 0x110a
                            || c == 0x110d
                            || (c >= 0x1113 && c <= 0x113b)
                            || c == 0x113d
                            || c == 0x113f
                            || (c >= 0x1141 && c <= 0x114b)
                            || c == 0x114d
                            || c == 0x114f
                            || (c >= 0x1151 && c <= 0x1153)
                            || (c >= 0x1156 && c <= 0x1158)
                            || c == 0x1162
                            || c == 0x1164
                            || c == 0x1166
                            || c == 0x1168
                            || (c >= 0x116a && c <= 0x116c)
                            || (c >= 0x116f && c <= 0x1171)
                            || c == 0x1174
                            || (c >= 0x1176 && c <= 0x119d)
                            || (c >= 0x119f && c <= 0x11a2)
                            || (c >= 0x11a9 && c <= 0x11aa)
                            || (c >= 0x11ac && c <= 0x11ad)
                            || (c >= 0x11b0 && c <= 0x11b6)
                            || c == 0x11b9
                            || c == 0x11bb
                            || (c >= 0x11c3 && c <= 0x11ea)
                            || (c >= 0x11ec && c <= 0x11ef)
                            || (c >= 0x11f1 && c <= 0x11f8)
                            ;

                        case 0x20:
                            return c == 0x207f;

                        case 0x21:
                            return c == 0x2102
                                || c == 0x2107
                                || (c >= 0x210a && c <= 0x2113)
                                || c == 0x2115
                                || (c >= 0x2118 && c <= 0x211d)
                                || c == 0x2124
                                || c == 0x2128
                                || (c >= 0x212c && c <= 0x212d)
                                || (c >= 0x212f && c <= 0x2138)
                                || (c >= 0x2160 && c <= 0x217f)
                                ;

                        case 0x30:
                            return c >= 0x309b && c <= 0x309c;

                        case 0x31:
                            return c >= 0x3131 && c <= 0x318e;

                        case 0xf9:
                        case 0xfa:
                        case 0xfb:
                        case 0xfc:
                        case 0xfd:
                        case 0xfe:
                        case 0xff:
                            return true;
                    
                        default:
                            return false;
                    }
                }

                jbool JXmlChars::isLetter2(jchar c){
                    if (c >= 'a' && c <= 'z'){
                        return true;
                    }
                    if (c == '>'){
                        return false;
                    }
                    if (c >= 'A' && c <= 'Z'){
                        return true;
                    }
                    return false;

                    //TODO
                    // switch (JCharacter::getType (c)) {
                    //     case JCharacter::LOWERCASE_LETTER:      // Ll
                    //     case JCharacter::UPPERCASE_LETTER:      // Lu
                    //     case JCharacter::OTHER_LETTER:          // Lo
                    //     case JCharacter::TITLECASE_LETTER:      // Lt
                    //     case JCharacter::LETTER_NUMBER:         // Nl
                    //     case JCharacter::COMBINING_SPACING_MARK:    // Mc
                    //     case JCharacter::ENCLOSING_MARK:        // Me
                    //     case JCharacter::NON_SPACING_MARK:      // Mn
                    //     case JCharacter::MODIFIER_LETTER:       // Lm
                    //     case JCharacter::DECIMAL_DIGIT_NUMBER:      // Nd
                    //         return !isCompatibilityChar(c) && !(c >= 0x20dd && c <= 0x20e0);

                    //     default:
                    //         return c == 0x0387;
                    // }
                }

                jbool JXmlChars::isDigit(jchar c){
                    return !( (c >= 0xff10) && (c <= 0xff19)); //TODO && JCharacter::isDigit(c)
                }

                jbool JXmlChars::isExtender(jchar c){
                    return c == 0x00b7 || c == 0x02d0 || c == 0x02d1 || c == 0x0387
                        || c == 0x0640 || c == 0x0e46 || c == 0x0ec6
                        || c == 0x3005 || (c >= 0x3031 && c <= 0x3035)
                        || (c >= 0x309d && c <= 0x309e)
                        || (c >= 0x30fc && c <= 0x30fe)
                        ;
                }

                JXmlChars::~JXmlChars(){
                }
            }
        }
    }
}
