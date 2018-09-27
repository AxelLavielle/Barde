define({ "api": [
  {
    "type": "get",
    "url": "/info",
    "title": "Example route",
    "name": "Example",
    "group": "Auth",
    "version": "0.0.0",
    "filename": "app/routes/auth.js",
    "groupTitle": "Auth"
  },
  {
    "type": "post",
    "url": "/auth/login",
    "title": "Login user",
    "group": "Auth",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\",\n  \"password\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content created\"\n  \"data\": {\n     \"token\": \"JWT \" + token,\n     \"message\": \"You are connected.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - User not exist",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": \"The email or password is incorrect.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "400 - Wrong content",
          "content": "{\n  \"msg\": \"Wrong content\"\n  \"data\": {\n     \"message\": \"The email or password is incorrect.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/auth.js",
    "groupTitle": "Auth",
    "name": "PostAuthLogin"
  },
  {
    "type": "post",
    "url": "/auth/register",
    "title": "Register user",
    "group": "Auth",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\",\n  \"password\": \"\",\n  \"firstName\": \"\",\n  \"lastName\": \"\",\n  \"userName\": \"\",\n  \"yearOfBirth\": \"\",\n  \"monthOfBirth\": \"\",\n  \"dayOfBirth\": \"\",\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content created\"\n  \"data\": {\n     \"message\": \"You are now registered.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "409 - User already exists",
          "content": "{\n  \"msg\": \"Content already exists\"\n  \"data\": {\n     \"message\": \"The email address or the username you have used is already registered.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "400 - Email validation failed",
          "content": "{\n  \"msg\": \"Content validation\"\n  \"data\": {\n     \"message\": \"The email format is wrong.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "400 - DateOfBirth validation failed",
          "content": "{\n  \"msg\": \"Content validation\"\n  \"data\": {\n     \"message\": \"The date of birth is wrong.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/auth.js",
    "groupTitle": "Auth",
    "name": "PostAuthRegister"
  },
  {
    "type": "get",
    "url": "/auth/isAdmin",
    "title": "Check if user is Admin",
    "name": "isAdmin",
    "group": "Auth",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"isAdmin\": true\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "403 - Forbidden",
          "content": "{\n  \"msg\": \"Forbidden\"\n  \"data\": {\n     \"isAdmin\": false\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/auth.js",
    "groupTitle": "Auth"
  },
  {
    "type": "get",
    "url": "/auth/isAuthenticate",
    "title": "Check if user is authenticate",
    "name": "isAuthenticate",
    "group": "Auth",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"isAuthenticate\": true\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "403 - Forbidden",
          "content": "{\n  \"msg\": \"Forbidden\"\n  \"data\": {\n     \"isAuthenticate\": false\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/auth.js",
    "groupTitle": "Auth"
  },
  {
    "type": "post",
    "url": "/captcha/verify",
    "title": "Verify if client is bot",
    "name": "Verify",
    "group": "Captcha",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"response\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"message\": \"\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - Error",
          "content": "{\n  \"msg\": \"Error\"\n  \"data\": {\n     \"message\": \"\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/captcha.js",
    "groupTitle": "Captcha",
    "groupDescription": "<p>All routes for captcha</p>"
  },
  {
    "type": "delete",
    "url": "/email/",
    "title": "Delete email",
    "name": "DeleteEmail",
    "group": "Email",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content deleted\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/email.js",
    "groupTitle": "Email",
    "groupDescription": "<p>All routes for email</p>"
  },
  {
    "type": "get",
    "url": "/email",
    "title": "Get all email",
    "name": "GetAllEmail",
    "group": "Email",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"emails\": []\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/email.js",
    "groupTitle": "Email",
    "groupDescription": "<p>All routes for email</p>"
  },
  {
    "type": "put",
    "url": "/email/",
    "title": "Add email",
    "group": "Email",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - No email",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": \"Vous devez inscrire votre email.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "304 - Already exists",
          "content": "{\n  \"msg\": \"Content already exists\"\n  \"data\": {\n     \"message\": \"Vous êtes déjà inscrit à nos newsletters !\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Email added",
          "content": "{\n  \"msg\": \"Content added\"\n  \"data\": {\n     \"message\": \"Votre inscription a bien été pris en compte.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/email.js",
    "groupTitle": "Email",
    "groupDescription": "<p>All routes for email</p>",
    "name": "PutEmail"
  },
  {
    "type": "post",
    "url": "/email/send",
    "title": "Send email",
    "name": "SendEmail",
    "group": "Email",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content send\"\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - Success",
          "content": "{\n  \"msg\": \"Error\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/email.js",
    "groupTitle": "Email",
    "groupDescription": "<p>All routes for email</p>"
  },
  {
    "type": "patch",
    "url": "/email/",
    "title": "Update email",
    "name": "UpdateEmail",
    "group": "Email",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content updated\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/email.js",
    "groupTitle": "Email",
    "groupDescription": "<p>All routes for email</p>"
  },
  {
    "type": "delete",
    "url": "/playlist",
    "title": "Delete playlist",
    "group": "Playlist",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"idPlaylist\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"message\": \"Playlist deleted.\"\n   }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item\"\n  \"data\": {\n     \"message\": \"Playlist not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "DeletePlaylist"
  },
  {
    "type": "delete",
    "url": "/playlist/music",
    "title": "Delete music in playlist",
    "group": "Playlist",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"idPlaylist\": \"\"\n  \"idMusic\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"message\": \"Music deleted.\"\n   }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item\"\n  \"data\": {\n     \"message\": \"Playlist not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item\"\n  \"data\": {\n     \"message\": \"Music not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "DeletePlaylistMusic"
  },
  {
    "type": "get",
    "url": "/playlist",
    "title": "Get all playlists",
    "group": "Playlist",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"playlists\": []\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "GetPlaylist"
  },
  {
    "type": "get",
    "url": "/playlist/count",
    "title": "Get number of playlists",
    "group": "Playlist",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"count\": Number\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "GetPlaylistCount"
  },
  {
    "type": "get",
    "url": "/playlist/:id",
    "title": "Get one playlist",
    "group": "Playlist",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"playlist\": {}\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "GetPlaylistId"
  },
  {
    "type": "get",
    "url": "/playlist/:perPage/:page",
    "title": "Get playlists by page",
    "group": "Playlist",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"playlists\": [],\n     \"page\": Number,\n     \"count\": Number\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "GetPlaylistPerpagePage"
  },
  {
    "type": "post",
    "url": "/playlist",
    "title": "New playlist",
    "group": "Playlist",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"name\": \"\",\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content created\"\n  \"data\": {\n     \"message\": \"Playlist saved.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "PostPlaylist"
  },
  {
    "type": "post",
    "url": "/playlist/music",
    "title": "Add music to playlist",
    "group": "Playlist",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"idPlaylist\": \"\",\n  \"name\": \"\",\n  \"bpm\": \"\",\n  \"seed\": \"\",\n  \"chords\": [],\n  \"arpege\": [],\n  \"instruments\": [],\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content created\"\n  \"data\": {\n     \"message\": \"Playlist saved.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "PostPlaylistMusic"
  },
  {
    "type": "put",
    "url": "/playlist",
    "title": "Update playlist",
    "group": "Playlist",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"name\": \"\",\n  \"idPlaylist\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content updated\"\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"Playlist not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "PutPlaylist"
  },
  {
    "type": "put",
    "url": "/playlist/music",
    "title": "Update music in playlist",
    "group": "Playlist",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"idPlaylist\": \"\",\n  \"idMusic\": \"\",\n  \"name\": \"\",\n  \"bpm\": \"\",\n  \"seed\": \"\",\n  \"chords\": [],\n  \"arpege\": [],\n  \"instruments\": [],\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content created\"\n  \"data\": {\n     \"message\": \"Playlist saved.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"Playlist not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"Music not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/playlist.js",
    "groupTitle": "Playlists",
    "groupDescription": "<p>All routes for playlists</p>",
    "name": "PutPlaylistMusic"
  },
  {
    "type": "get",
    "url": "/report",
    "title": "Get all reports",
    "group": "Report",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"reports\": []\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/report.js",
    "groupTitle": "Reports",
    "groupDescription": "<p>All routes for reports</p>",
    "name": "GetReport"
  },
  {
    "type": "get",
    "url": "/report/count",
    "title": "Get number of reports",
    "group": "Report",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"count\": Number\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/report.js",
    "groupTitle": "Reports",
    "groupDescription": "<p>All routes for reports</p>",
    "name": "GetReportCount"
  },
  {
    "type": "get",
    "url": "/report/:perPage/:page",
    "title": "Get reports by page",
    "group": "Report",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"reports\": [],\n     \"page\": Number,\n     \"count\": Number\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/report.js",
    "groupTitle": "Reports",
    "groupDescription": "<p>All routes for reports</p>",
    "name": "GetReportPerpagePage"
  },
  {
    "type": "post",
    "url": "/report",
    "title": "New report",
    "group": "Report",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"description\": \"\",\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content created\"\n  \"data\": {\n     \"message\": \"Report saved.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "400 - Device param is wrong",
          "content": "{\n  \"msg\": \"Content validation\"\n  \"data\": {\n     \"message\": \"The device is wrong.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/report.js",
    "groupTitle": "Reports",
    "groupDescription": "<p>All routes for reports</p>",
    "name": "PostReport"
  },
  {
    "type": "put",
    "url": "lang/content",
    "title": "Get all traduction content",
    "name": "addContent",
    "group": "Translation",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n\"msg\": \"Content added\",\n\"data\": {\n   \"message\": \"Le contenu à bien été ajouté\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/multilanguage.js",
    "groupTitle": "Translation",
    "groupDescription": "<p>All routes for translation</p>"
  },
  {
    "type": "put",
    "url": "/lang/translation",
    "title": "add translation to a content",
    "name": "addTranslation",
    "group": "Translation",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"Traduction\": [\n         \"content_id\": \"NAV_HOME_TITLE\",\n       \"content_value\": [\n       {\n         \"content\": \"Home\",\n         \"lang_code\": \"us\",\n         },\n       ]\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/multilanguage.js",
    "groupTitle": "Translation",
    "groupDescription": "<p>All routes for translation</p>"
  },
  {
    "type": "get",
    "url": "lang/content",
    "title": "Get all traduction content",
    "name": "getContent",
    "group": "Translation",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"Traduction\": [\n         \"content_id\": \"NAV_HOME_TITLE\",\n       \"content_value\": [\n       {\n         \"content\": \"Home\",\n         \"lang_code\": \"us\",\n         },\n       ]\n  }\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/multilanguage.js",
    "groupTitle": "Translation",
    "groupDescription": "<p>All routes for translation</p>"
  },
  {
    "type": "post",
    "url": "/lang/getTranslation",
    "title": "get Translated data",
    "name": "getTranslation",
    "group": "Translation",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n     \"data\": \"EQUIPE\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/multilanguage.js",
    "groupTitle": "Translation",
    "groupDescription": "<p>All routes for translation</p>"
  },
  {
    "type": "delete",
    "url": "/user/",
    "title": "Delete user",
    "name": "DeleteUser",
    "group": "User",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"message\": \"User deleted.\"\n   }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>"
  },
  {
    "type": "get",
    "url": "/user",
    "title": "Get all users",
    "group": "User",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"users\": []\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "GetUser"
  },
  {
    "type": "get",
    "url": "/user/count",
    "title": "Get number of users",
    "group": "User",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"count\": Number\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "GetUserCount"
  },
  {
    "type": "get",
    "url": "/user/:email",
    "title": "Get one users",
    "group": "User",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"user\": {}\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "GetUserEmail"
  },
  {
    "type": "get",
    "url": "/user/me",
    "title": "Get user authenticated",
    "group": "User",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"user\": []\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "GetUserMe"
  },
  {
    "type": "get",
    "url": "/user/password/reset",
    "title": "Ask password reset",
    "group": "User",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"message\": \"Email sent.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "400 - Email error",
          "content": "{\n  \"msg\": \"Error\"\n  \"data\": {\n     \"message\": \"Email error.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Wait 2hour",
          "content": "{\n  \"msg\": \"Wait\"\n  \"data\": {\n     \"message\": \"You need to wait before send a new email.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "GetUserPasswordReset"
  },
  {
    "type": "get",
    "url": "/user/:perPage/:page",
    "title": "Get users by page",
    "group": "User",
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"users\": [],\n     \"page\": Number,\n     \"count\": Number\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "GetUserPerpagePage"
  },
  {
    "type": "patch",
    "url": "/user/",
    "title": "Update user (Partially)",
    "group": "User",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\",\n  \"userNAme\": \"\",\n  \"password\": \"\",\n  \"firstName\": \"\",\n  \"lastName\": \"\",\n  \"yearOfBirth\": \"\",\n  \"monthOfBirth\": \"\",\n  \"dayOfBirth\": \"\",\n  \"role\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content updated\"\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - Email is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": \"Email cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "409 - User already exists",
          "content": "{\n  \"msg\": \"Content already exists\"\n  \"data\": {\n     \"message\": \"The username you have used is already registered.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "PatchUser"
  },
  {
    "type": "post",
    "url": "/user/password/reset",
    "title": "Reset password",
    "group": "User",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"token\": \"\",\n  \"password\": \"\",\n  \"email\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Success\"\n  \"data\": {\n     \"message\": \"Email sent.\"\n  }\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "400 - No token",
          "content": "{\n  \"msg\": \"Error\"\n  \"data\": {\n     \"message\": \"You need to ask for a token.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Expired or already used",
          "content": "{\n  \"msg\": \"Error\"\n  \"data\": {\n     \"message\": \"Token expired or already used.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "PostUserPasswordReset"
  },
  {
    "type": "put",
    "url": "/user/",
    "title": "Update user (Fully)",
    "group": "User",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\",\n  \"userName\": \"\",\n  \"password\": \"\",\n  \"firstName\": \"\",\n  \"lastName\": \"\",\n  \"yearOfBirth\": \"\",\n  \"monthOfBirth\": \"\",\n  \"dayOfBirth\": \"\",\n  \"role\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content updated\"\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "409 - User already exists",
          "content": "{\n  \"msg\": \"Content already exists\"\n  \"data\": {\n     \"message\": \"The username you have used is already registered.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "PutUser"
  },
  {
    "type": "put",
    "url": "/user/password",
    "title": "Update user's password",
    "group": "User",
    "parameter": {
      "examples": [
        {
          "title": "Request-Example:",
          "content": "{\n  \"email\": \"\",\n  \"password\": \"\",\n  \"newPassword\": \"\"\n}",
          "type": "json"
        }
      ]
    },
    "success": {
      "examples": [
        {
          "title": "200 - Success",
          "content": "{\n  \"msg\": \"Content updated\"\n}",
          "type": "json"
        }
      ]
    },
    "error": {
      "examples": [
        {
          "title": "400 - One param is empty",
          "content": "{\n  \"msg\": \"No content\"\n  \"data\": {\n     \"message\": param + \" cannot be empty.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "404 - Not found",
          "content": "{\n  \"msg\": \"Can't find item.\"\n  \"data\": {\n     \"message\": \"User not exists.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Wrong password",
          "content": "{\n  \"msg\": \"Unauthorized\"\n  \"data\": {\n     \"message\": \"Wrong password.\"\n  }\n}",
          "type": "json"
        },
        {
          "title": "401 - Unauthorized",
          "content": "{\n  \"Unauthorized\"\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "app/routes/user.js",
    "groupTitle": "Users",
    "groupDescription": "<p>All routes for users</p>",
    "name": "PutUserPassword"
  }
] });
