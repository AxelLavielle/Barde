//
//  SettingsEditAccountView.swift
//  Barde
//
//  Created by Arnaud Perrault on 17/11/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData
import SwiftSpinner

class SettingsEditAccountView: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var tfFirstName: UITextField!
    @IBOutlet weak var tfLastName: UITextField!
    @IBOutlet weak var tfUserName: UITextField!
    @IBOutlet weak var tfBirthDate: UITextField!
    @IBOutlet weak var buttonBack: UIBarButtonItem!
    
    var profilFromLocal: Profil? // optional
    var userService: UserService?

    let datePicker = UIDatePicker()
    
    func createDatePicker() {
        datePicker.datePickerMode = .date
        datePicker.maximumDate = Date.init()

        tfBirthDate.inputView = datePicker
        datePicker.addTarget(self, action: #selector(datePickerValueChanged(_:)), for: .valueChanged)
    }
    
    @objc func datePickerValueChanged(_ sender: Any) {
       let dateFormatter = DateFormatter()
        
        dateFormatter.dateStyle = .short
        dateFormatter.timeStyle = .none
        dateFormatter.dateFormat = NSLocalizedString("Date.format", comment: "")
        
        tfBirthDate.text = dateFormatter.string(from: datePicker.date)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        
        configureView()
        
        userService = UserService()
        loadUserData()
    }
    
    func configureView() {
        
        createDatePicker()
        
        self.navigationItem.title = NSLocalizedString("MyAccount.text", comment: "")
        
    
        tfFirstName.leftView =  UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        tfFirstName.leftViewMode = .always
        
        tfLastName.leftView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        tfLastName.leftViewMode = .always

        tfUserName.leftView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        tfUserName.leftViewMode = .always

        tfBirthDate.leftView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        tfBirthDate.leftViewMode = .always
        
        tfFirstName.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
        tfLastName.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
        tfUserName.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
        tfBirthDate.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
    }
  
    @IBAction func saveButton(_ sender: Any) {

        saveUserData()
        
        
        ad.saveContext()

    }
    
    func saveUserData() {
        var profil: Profil!
        
        profil = profilFromLocal
        
        if let firstname = tfFirstName.text{
            profil.firstname = firstname

            
            if (!firstname.isEmpty)
            {
                profil.firstname = firstname
                UserDefaults.standard.set(firstname, forKey:  "firstname")
            }
//            else {
//                let refreshAlert = UIAlertController(title: "Invalid \"Firstname\" field.", message: "Field \"Firstname\" can't be empty.", preferredStyle: UIAlertController.Style.alert)
//
//                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
//                }))
//
//                present(refreshAlert, animated: true, completion: nil)
//            }
        }
        if let lastname = tfLastName.text{
            if (!lastname.isEmpty)
            {
                profil.lastname = lastname
                UserDefaults.standard.set(lastname,  forKey: "lastname")
            }
//            else {
//                let refreshAlert = UIAlertController(title: "Invalid \"Lastname\" field.", message: "Field \"Lastname\" can't be empty.", preferredStyle: UIAlertController.Style.alert)
//
//                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
//                }))
//
//                present(refreshAlert, animated: true, completion: nil)
//            }
        }
        if let userName = tfUserName.text{
            if (!userName.isEmpty)
            {
                profil.username = userName
                UserDefaults.standard.set(userName, forKey: "username")

            }
//            else {
//                let refreshAlert = UIAlertController(title: "Invalid \"Username\" field.", message: "Field \"Username\" can't be empty.", preferredStyle: UIAlertController.Style.alert)
//
//                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
//                }))
//
//                present(refreshAlert, animated: true, completion: nil)
//            }
        }
        if let birthdate = tfBirthDate.text{
            if (!birthdate.isEmpty)
            {
                profil.birthdate = birthdate
                
                let dateFormatter = DateFormatter()
                
                dateFormatter.dateStyle = .short
                dateFormatter.timeStyle = .none
                dateFormatter.dateFormat = "YYYY-MM-dd"
                let date = dateFormatter.date(from: birthdate as! String)

                UserDefaults.standard.set(date,  forKey: "birthdate")
            }
//            else {
//                let refreshAlert = UIAlertController(title: "Invalid \"Birthdate\" field.", message: "Field \"Birthdate\" can't be empty.", preferredStyle: UIAlertController.Style.alert)
//                
//                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
//                }))
//                
//                present(refreshAlert, animated: true, completion: nil)
//            }
        }
        
    }
    
    func loadUserData(){
        tfFirstName.text = UserDefaults.standard.string(forKey: "firstname")
        tfLastName.text = UserDefaults.standard.string(forKey: "lastname")
        tfUserName.text = UserDefaults.standard.string(forKey: "username")
        tfBirthDate.text = UserDefaults.standard.string(forKey: "birthdate")
        
//        if let profil = profilFromLocal{
//            tfFirstName.text = profil.firstname
//            tfLastName.text = profil.lastname
//            tfUserName.text = profil.username
//            tfBirthDate.text = profil.birthdate
//        }
    }
    
    func textFieldDidBeginEditing(_ textField: UITextField) {
        self.navigationItem.setHidesBackButton(true, animated: true)
        
        navigationItem.rightBarButtonItem = UIBarButtonItem(title: "OK", style: .plain, target: self, action: #selector(validChange(_:)))
        navigationItem.leftBarButtonItem = UIBarButtonItem(title: NSLocalizedString("Cancel.text", comment: ""), style: .plain, target: self, action: #selector(dismissChange(_:)))
    }
    
    @objc func validChange(_ sender: Any) {
        SwiftSpinner.show(NSLocalizedString("Loading.text", comment: ""))

        self.navigationItem.setHidesBackButton(false, animated: false)
        self.navigationItem.rightBarButtonItem = nil;

        let back = UIBarButtonItem(title: NSLocalizedString("Back.text", comment: ""), style: .plain, target: self, action: #selector(backButtonAction))
        self.navigationItem.leftBarButtonItem = back;
        
        tfFirstName.resignFirstResponder()
        tfLastName.resignFirstResponder()
        tfUserName.resignFirstResponder()
        tfBirthDate.resignFirstResponder()
        self.view.endEditing(true)
        // saveUserData()

        // let userData: NSManagedObject = (userService?.getLocalData())!
        let inputFormatter = DateFormatter()
        
        var date = ""
        if (Locale.current.languageCode == "fr")
        {
            inputFormatter.dateFormat = "dd/MM/yyyy"
            let showDate = inputFormatter.date(from: tfBirthDate.text!)
            inputFormatter.dateFormat = "yyyy-MM-dd"
            date = inputFormatter.string(from: showDate!)
        } else {
            inputFormatter.dateFormat = "yyyy-MM-dd"
            let showDate = inputFormatter.date(from: tfBirthDate.text!)
            date = inputFormatter.string(from: showDate!)
        }

        
        UserDefaults.standard.set(date,  forKey: "birthdate")
        
        userService?.updateUserData(tfFirstName: tfFirstName.text!, tfLastName: tfLastName.text!, tfUserName: tfUserName.text!, tfBirthDate: date, email: UserDefaults.standard.string(forKey: "email")!)

        SwiftSpinner.hide()

    }
    
    @objc func dismissChange(_ sender: Any) {
        self.navigationItem.setHidesBackButton(false, animated: false)
        self.navigationItem.rightBarButtonItem = nil;
        let back = UIBarButtonItem(title: NSLocalizedString("Back.text", comment: ""), style: .plain, target: self, action: #selector(backButtonAction))

        self.navigationItem.leftBarButtonItem = back;
        loadUserData()
        tfFirstName.resignFirstResponder()
        tfLastName.resignFirstResponder()
        tfUserName.resignFirstResponder()
        tfBirthDate.resignFirstResponder()
    }
    @IBAction func backButtonAction(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
}

