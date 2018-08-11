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
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        DispatchQueue.main.async { vc.present(alert, animated: true, completion: nil) }
    }
    
    static func showIncompleteForm(on vc:UIViewController) {
        showBasic(on: vc, with: "Incomplete form", message: "Please fill out all fields in the form")
    }
    
    static func showRequiredField (on vc:UIViewController) {
        showBasic(on: vc, with: "Incomplete form", message: "Please fill out all required fields in the form")
    }
    
    static func showUnableToRetrieveData(on vc: UIViewController) {
        showBasic(on: vc, with: "Unable to retrieve data", message: "Network error")
    }
    
    static func showUnableToConnectToGeneratorServer(on vc:UIViewController) {
        showBasic(on: vc, with: "Unable to connect to generator server", message: "Network error")
    }
    
    static func showUnableToConnectToDataServer(on vc:UIViewController) {
        showBasic(on: vc, with: "Unable to connect to data server", message: "Network error")
    }
    
    static func showAction (on vc: UIViewController, with title:String, message: String) -> UIAlertController {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        
        return alertController
    }
    
    static func showLogoutAction(on vc: UIViewController) {
        let alert = showAction(on: vc, with: "Log out", message: "Would you like to log out ?")
      
        alert.addAction(UIAlertAction(title: "Log out", style: .destructive, handler: { (action) -> Void in
            print("Delete button tapped")
            Utils().deleteAllRecord(entity: "Profil")
            UserDefaults.standard.removeObject(forKey: "Token")
            
            let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
            let newViewController = storyBoard.instantiateViewController(withIdentifier: "FirstPageViewController") as! FirstPageViewController
            vc.present(newViewController, animated: true, completion: nil)
        }))
        
        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: { (action) -> Void in
            print("Cancel button tapped")
        }))
        
        //alert.popoverPresentationController?.sourceView = vc.view
        vc.present(alert, animated: true, completion: nil)
    }
}

