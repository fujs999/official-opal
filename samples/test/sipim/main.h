/*
 * main.h
 *
 * OPAL application source file for seing IM via SIP
 *
 * Copyright (c) 2008 Post Increment
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Open Phone Abstraction Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 */

#ifndef _SipIM_MAIN_H
#define _SipIM_MAIN_H

#include <opal/console_mgr.h>


#if !OPAL_HAS_IM
#error Cannot compile IM sample program without IM!
#endif


class MyManager : public OpalManagerCLI
{
    PCLASSINFO(MyManager, OpalManagerCLI);
  public:
    MyManager() : m_imEP(NULL) { }

    virtual PString GetArgumentSpec() const override;
    virtual void Usage(ostream & strm, const PArgList & args) override;
    virtual bool Initialise(PArgList & args, bool verbose, const PString & defaultRoute = PString::Empty()) override;

  protected:
    OpalIMEndPoint * m_imEP;

    bool GetToFromURL(const PArgList & args, PURL & to, PURL & from);

    virtual void OnConversation(const OpalIMContext::ConversationInfo & info) override;
    virtual void OnMessageReceived(const OpalIM & message) override;
    virtual void OnMessageDisposition(const OpalIMContext::DispositionInfo & info) override;
    virtual void OnCompositionIndication(const OpalIMContext::CompositionInfo & info) override;

    PDECLARE_NOTIFIER(PCLI::Arguments, MyManager, CmdSend);
    PDECLARE_NOTIFIER(PCLI::Arguments, MyManager, CmdComp);

    PDECLARE_NOTIFIER(PCLI::Arguments, MyManager, CmdSet);
    PStringToString m_variables;
};


#endif  // _SipIM_MAIN_H


// End of File ///////////////////////////////////////////////////////////////
