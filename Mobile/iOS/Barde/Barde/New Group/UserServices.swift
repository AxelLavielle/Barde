//
//  UserServices.swift
//  Barde
//
//  Created by Arnaud Perrault on 24/02/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import CoreData
import Alamofire

class UserService {
    
    func getLocalData() -> NSManagedObject? {
        let request = NSFetchRequest<NSFetchRequestResult>(entityName: "Profil")
        //request.predicate = NSPredicate(format: "age = %@", "12")
        request.returnsObjectsAsFaults = false
        request.fetchLimit = 1
        
        do {
            let result = try context.fetch(request)
            
            for data in result as! [NSManagedObject] {
                return data
            }
        } catch {
            print("Failed")
        }
        
        return nil
    }
    
    func updateUserData(data: NSManagedObject) {
        let headers: HTTPHeaders = [
            "Authorization": UserDefaults.standard.string(forKey: "Token")!,
            ]
        
        print("birtdate", data.value(forKey:"birthdate") as! String)
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "MM/dd/yyyy"
        let date = dateFormatter.date(from: data.value(forKey:"birthdate") as! String)
        dateFormatter.dateFormat = "MM"
        let strMonth = dateFormatter.string(from: date!)
        dateFormatter.dateFormat = "yyyy"
        let strYear = dateFormatter.string(from: date!)
        dateFormatter.dateFormat = "dd"
        let strDay = dateFormatter.string(from: date!)
        
        let parameters: Parameters = [
            "email":  data.value(forKey:"email") as! String,
            "yearOfBirth": strYear,
            "monthOfBirth": strMonth,
            "dayOfBirth": strDay,
            "firstName": data.value(forKey:"firstname") as! String,
            "lastName": data.value(forKey:"lastname") as! String,
            "userName": data.value(forKey:"username") as! String,
            ]
        
        print(headers);
        
        Alamofire.request(Utils().getApiUrl() + "/user/", method:.put, parameters: parameters, headers: headers).responseJSON { response in
            print("Request: \(String(describing: response.request))")   // original url request
            print("Response: \(String(describing: response.response))") // http url response
            print("Result: \(String(describing: response.result.value))")
            // response serialization result
            
            if let httpStatusCode = response.response?.statusCode {
                switch(httpStatusCode) {
                case 200:
                    if ((response.result.value) != nil) {
                        
                    }
                    break
                case 400:
                    
                    break
                default:
                    print("default")
                    
                }
            }
        }
    }
}
