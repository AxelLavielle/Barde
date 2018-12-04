//
//  AlertServices.swift
//  Barde
//
//  Created by Arnaud Perrault on 28/07/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

struct Alert {
    
    static func showBasic (on vc:UIViewController, with title: String, message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertController.Style.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        DispatchQueue.main.async { vc.present(alert, animated: true, completion: nil) }
    }
    
    static func showIncompleteForm(on vc:UIViewController) {
        showBasic(on: vc, with: NSLocalizedString("IncompleteForm.text", comment: ""), message: NSLocalizedString("IncompleteFormDescription.text", comment: ""))
    }
    
    static func showRequiredField (on vc:UIViewController) {
        showBasic(on: vc, with: NSLocalizedString("IncompleteForm.text", comment: ""), message: NSLocalizedString("IncompleteForm.text", comment: ""))
    }
    
    static func showUnableToRetrieveData(on vc: UIViewController) {
        showBasic(on: vc, with: NSLocalizedString("UnableToRetrieveData.text", comment: ""), message: NSLocalizedString("UnableToRetrieveDataDescription.text", comment: ""))
    }
    
    static func showUnableToConnectToGeneratorServer(on vc:UIViewController) {
        showBasic(on: vc, with: NSLocalizedString("UnableToConnectToGeneratorServer.text", comment: ""), message: NSLocalizedString("UnableToConnectToGeneratorServerDescription.text", comment: ""))
    }
    
    static func showUnableToConnectToDataServer(on vc:UIViewController) {
        showBasic(on: vc, with:  NSLocalizedString("UnableToConnectToDataServer.text", comment: ""), message:  NSLocalizedString("UnableToConnectToDataServerDescription.text", comment: ""))
    }
    
    static func showAction (on vc: UIViewController, with title:String, message: String) -> UIAlertController {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        
        return alertController
    }
    
    static func showLogoutAction(on vc: UIViewController) {
        let alert = showAction(on: vc, with: NSLocalizedString("LogOut.text", comment: ""), message: NSLocalizedString("LogOutDescription.text", comment: ""))
      
        alert.addAction(UIAlertAction(title: NSLocalizedString("LogOut.text", comment: ""), style: .destructive, handler: { (action) -> Void in
            print("Delete button tapped")
            Utils().deleteAllRecord(entity: "Profil")
            UserDefaults.standard.removeObject(forKey: "Token")
            
            let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "FirstPageViewController") as! FirstPageViewController
            vc.present(newViewController, animated: true, completion: nil)
        }))
        
        alert.addAction(UIAlertAction(title: NSLocalizedString("Cancel.text", comment: ""), style: .cancel, handler: { (action) -> Void in
            print("Cancel button tapped")
        }))
        
        //alert.popoverPresentationController?.sourceView = vc.view
        vc.present(alert, animated: true, completion: nil)
    }
    
    static func showReconnectAction(on vc: UIViewController) {
        let alert = showAction(on: vc, with: NSLocalizedString("ConnectionLost.text", comment: ""), message: NSLocalizedString("ConnectionLostDescription.text", comment: ""))
        
        alert.addAction(UIAlertAction(title: NSLocalizedString("ConnectionLostButton.text", comment: ""), style: .default, handler: { (action) -> Void in
            SocketManager.sharedInstance.establishConnection()
        }))
    
        //alert.popoverPresentationController?.sourceView = vc.view
        vc.present(alert, animated: true, completion: nil)
    }
    
    
    static func showOfflinePage(on vc: UIViewController) -> Void {
        DispatchQueue.main.async {
            vc.performSegue(withIdentifier: "NetworkUnavailable", sender: vc)
        }
    }
    
    static func showMainPage(on vc: UIViewController) -> Void {
        DispatchQueue.main.async {
            vc.performSegue(withIdentifier: "ToRootView", sender: vc)
        }
    }
    
    static func showUnableToInitializeData(on vc: UIViewController) -> Void {
        showBasic(on: vc, with: NSLocalizedString("UnableToInitializeData.text", comment: ""), message: NSLocalizedString("UnableToInitializeDataDescription.text", comment: ""))
    }
}

