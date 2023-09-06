#include <iostream>
#include <stdio.h>

#include "Acceptor.h"
#include "Helper.h"

MPOST::CAcceptor* acceptor;

void CreateAcceptor() {
  acceptor = new MPOST::CAcceptor;
  //acceptor->Open("tty", MPOST::A);
}

void OpenAcceptor() {
  acceptor->Open("tty", MPOST::A);
}

void CloseAcceptor() {
  acceptor->Close();
}

void EnableAcceptor() {
  bool a = true;
  acceptor->SetEnableAcceptance(a);
}

int AutomaticLoopAcceptor() {
  acceptor->Open("tty", MPOST::A);

  bool a = true;
  acceptor->SetEnableAcceptance(a);
  acceptor->SetAutoStack(a);
  enum MPOST::State current_state; 
  
  while (true)
  { 
    current_state = acceptor->GetDeviceState();
    cout << current_state << endl;
    if (current_state == MPOST::Stacked) {
      cout << acceptor->GetBill().ToString() << endl;
    }
  }
  return 1;
}

int RunLoop() {
  string s;
    
  while(true)
  {
    cin >> s;
    
    if (s == "o")
      acceptor->Open("tty", MPOST::A);
    
    if (s == "c")
      acceptor->Close();
    
    if ( s == "a"){
      bool a = true;
      acceptor->SetEnableAcceptance(a);
      // acceptor->SetAutoStack(a); 
    }

    if (s  == "bt"){
      for(unsigned int i = 0; i < acceptor->GetBillValues().size();i++){
        cout << acceptor->GetBillValues()[i].ToString() << endl;
      }
    }
    
    if (s  == "b"){
        cout << acceptor->GetBill().ToString() << endl;
    }

    if  (s == "gc"){
      cout << acceptor->GetCashBoxTotal() << endl;
    }

    // Exit
    if (s == "x")
      break;
    
    if (s == "r")
      acceptor->EscrowReturn();
    
    if (s == "s")
      acceptor->EscrowStack();    
    
    if (s == "res")
      acceptor->SoftReset();    
    
    // Hard-code the appropriate filename here (or add code to read a filename).
    // if (s == "f")
    // 	acceptor->FlashDownload("/root/workspace/MPOST/284us281.bds");//490021211_SC83_JPY_FLASH.BIN");
    
    // Device Information
    if (s == "i")
    {
      cout << "     Device Type: " <<(acceptor->GetCapDeviceType() ? acceptor->GetDeviceType() : "Not supported") << endl;
      cout << "       Device CRC: " << acceptor->GetDeviceCRC() << endl;
      cout << "        Serial #: " <<(acceptor->GetCapDeviceSerialNumber() ? acceptor->GetDeviceSerialNumber() : "Not supported") << endl;
      cout << "     Boot Part #: " <<(acceptor->GetCapBootPN() ? acceptor->GetBootPN() : "Not supported") << endl;
      cout << "  Application PN: " <<(acceptor->GetCapApplicationPN() ? acceptor->GetApplicationPN() : "Not supported") << endl;
      if (acceptor->GetCapVariantPN())
      {
        cout << "       Variant PN: " << acceptor->GetVariantPN() << endl;
        cout << "    Variant Name: " << endl;
        
        vector<string> names = acceptor->GetVariantNames();
        
        for(vector<string>::iterator i = names.begin(); i != names.end(); i++)
          cout << *i << " ";
        
        cout << endl;
      }
      else
      {
        cout << "       Variant PN: Not supported";
        cout << "    Variant Name: Not supported" << endl;
      }
      
      cout << "        Cassette: " <<(acceptor->GetCashBoxAttached() ? "Installed" : "Not installed") << endl;
      cout << "Cash in Cassette: ";
      if (acceptor->GetCapCashBoxTotal())
        cout << acceptor->GetCashBoxTotal() << endl;
      else
        cout << "Not supported" << endl;
      
      cout << "           Resets: " << acceptor->GetDeviceResets() << endl;
      cout << "        Bill Path: " <<(acceptor->GetDeviceJammed() ? "Jammed" : "Clear") << endl;
      cout << "            Model: " << acceptor->GetDeviceModel();
      
      if (acceptor->GetDeviceModel() >= 32)
        cout << "(" <<(char)acceptor->GetDeviceModel() << ")" << endl;
      else
        cout << endl;
    
      cout << "        BNFStatus: ";
      if (acceptor->GetCapBNFStatus())
        cout << acceptor->GetBNFStatus() << endl;
      else
        cout << "Not supported" << endl;
      
      if (acceptor->GetCapAudit())
      {
        vector<int> values = acceptor->GetAuditLifeTimeTotals();
        cout << "             Data Map: " << values[0] << endl;
        cout << "       Total Op Hours: " << values[1] << endl;
        cout << "    Total Mot Starts: " << values[2] << endl;
        cout << "        Total Escrow: " << values[3] << endl;
        cout << "    Total Recognized: " << values[4] << endl;
        cout << "     Total Validated: " << values[5] << endl;

        values = acceptor->GetAuditQP();
        cout << "             Last 100: " << values[0] << endl;
        cout << "        Motor Starts: " << values[1] << endl;
        cout << "        Docs Stacked: " << values[2] << endl;
        cout << "          Docs Escrow: " << values[3] << endl;
        cout << "    Docs Recognition: " << values[4] << endl;
        cout << "       Docs Validated: " << values[5] << endl;
        cout << "     Docs Rec Reject: " << values[6] << endl;
        cout << "     Docs Sec Reject: " << values[7] << endl;
        cout << "  Docs Orient Reject: " << values[8] << endl;
        cout << "Docs Disabled Reject: " << values[9] << endl;
        cout << "       Docs FF Reject: " << values[10] << endl;
        cout << " Docs While Disabled: " << values[11] << endl;
        cout << "    Docs Host Reject: " << values[12] << endl;
        cout << "        Docs Barcode: " << values[13] << endl;

        values = acceptor->GetAuditPerformance();
        cout << "           CC0 Reject: " << values[0] << endl;
        cout << "           CC1 Reject: " << values[1] << endl;
        cout << "            All James: " << values[2] << endl;
        cout << "        Jam Recovery: " << values[3] << endl;
        cout << "           Jam Reject: " << values[4] << endl;
        cout << "          Jam Stacker: " << values[5] << endl;
        cout << "     Jam No Recovery: " << values[6] << endl;
        cout << "       Out of Service: " << values[7] << endl;
        cout << "        Out of Order: " << values[8] << endl;
        cout << "     Operating Hours: " << values[9] << endl;
        cout << "        Doc Too Long: " << values[10] << endl;
        cout << "            Doc Tease: " << values[11] << endl;
        cout << "        Calibrations: " << values[12] << endl;
        cout << "               Resets: " << values[13] << endl;
        cout << "            Downloads: " << values[14] << endl;
        cout << "        Cassette Full: " << values[15] << endl;
        cout << "    Cassette Removed: " << values[16] << endl;
      }
      else
      {
          cout << "          Performance: Not supported" << endl;
      }
    }
    
    if (s == "d")
      acceptor->SetDebugLog(!acceptor->GetDebugLog());
  }
        
    
  return 1;
}

// void AddEventListener(int eventType, void(*eventHandler)(MPOST::CAcceptor* acceptor, int value)) {
//   acceptor->SetEventHandler(MPOST::ConnectedEvent, eventHandler);
// }