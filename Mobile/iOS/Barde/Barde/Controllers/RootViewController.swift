//
//  RootViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 02/02/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import Alamofire
import SwiftyJSON
import CoreData

class RootViewController: UITabBarController, NSFetchedResultsControllerDelegate {
    
    var controller: NSFetchedResultsController <Profil>!
    
    override func viewDidLoad() {
        
        let headers: HTTPHeaders = [
            "Authorization": UserDefaults.standard.string(forKey: "Token")!,
            ]
        

        let email = UserDefaults.standard.string(forKey: "Email")!
        
        Alamofire.request(Utils().getApiUrl() + "/user/" + email, headers: headers).responseJSON { response in
            
            if let httpStatusCode = response.response?.statusCode {
                switch(httpStatusCode) {
                case 200:
                    if ((response.result.value) != nil) {
                        let data = JSON(response.result.value!)["data"]
                        
                        let entity = NSEntityDescription.entity(forEntityName: "Profil", in: context)
                        let profil = NSManagedObject(entity: entity!, insertInto: context)
                        
                        profil.setValue(data["user"]["email"].stringValue, forKey: "email")
                        profil.setValue(data["user"]["name"]["firstName"].stringValue, forKey: "firstname")
                        profil.setValue(data["user"]["name"]["lastName"].stringValue, forKey: "lastname")
                        profil.setValue(data["user"]["name"]["userName"].stringValue, forKey: "username")
                        
                        let dateFormatter = DateFormatter()
                        dateFormatter.locale = Locale(identifier: "en_US_POSIX") // edited
                        dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSSZ"
                        let date = dateFormatter.date(from: data["user"]["dateOfBirth"].stringValue)!
                        dateFormatter.dateFormat = "MM/dd/YYYY"
                        let dateString = dateFormatter.string(from: date)
                        
                        
                        profil.setValue(dateString, forKey: "birthdate")
                        
                        do {
                            try context.save()
                        } catch {
                            
                            print("Failed saving")
                        }
                        
                    }
                    break
                case 400:
                    let refreshAlert = UIAlertController(title: "Wrong content", message: "The email or password is incorrect.", preferredStyle: UIAlertControllerStyle.alert)
                    
                    refreshAlert.addAction(UIAlertAction(title: "Ok", style: .default, handler: { (action: UIAlertAction!) in
                    }))
                    
                    self.present(refreshAlert, animated: true, completion: nil)
                    break
                default:
                    print("default")
                    
                }
            }
        }
    }
}
