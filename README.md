
# 💼 Job Bank API

## 📌 About
This project provides a full-featured RESTful API for managing job listings, applications, and users. Built using FastAPI and PostgreSQL, it's designed for job seekers and recruiters alike.

### ✨ Features
- JWT authentication with role-based permissions (admin, recruiter, user)
- Create, update, and list job postings
- User registration and login
- Apply for jobs and list user applications
- Admins and recruiters can view candidates for a job

### ⚙️ Technologies
- Python 3.12+
- FastAPI
- SQLAlchemy ORM
- PostgreSQL (via Docker)
- JWT Auth (using python-jose)
- Pytest for testing

---

## ✅ Requirements

<details>
<summary>📦 Prerequisites (Running Locally)</summary>

- 🐍 **Python 3.10+**
- 📦 **pip** up to date
- 🧪 **virtualenv** (recommended)

</details>

<details>
<summary>🐳 Prerequisites (Using Docker - Recommended)</summary>

- 🐋 **Docker Engine** version 20.10+
- 🧩 **Docker Compose** version 1.29+  
  (or native `docker compose` from Docker Desktop)

</details>

<details>
<summary>💻 Operating System</summary>

- 🐧 **Linux**
- 🍎 **macOS**
- 🪟 **Windows** (with **WSL2 enabled**, if using Docker)

</details>

---

## 🚀 Instructions

### 1. Clone the repository
```bash
$ git clone https://github.com/yourusername/job-bank-api.git
$ cd job_bank
```

### 2. Build and run with Docker
```bash
$ docker-compose up --build
```

### 3. (Optional) Run locally
```bash
$ ./setup.sh
```

---

<details>
<summary>📚 API Endpoints Overview</summary>

### 🔐 Authentication
| Method | Endpoint         | Description              |
|--------|------------------|--------------------------|
| POST   | `/auth/register` | Register a new user      |
| POST   | `/auth/login`    | Login and get JWT token  |

### 👤 Users
| Method | Endpoint                  | Description                        |
|--------|---------------------------|------------------------------------|
| GET    | `/users/me/applications`  | List logged-in user's applications |

### 🏢 Companies
| Method | Endpoint      | Description        |
|--------|---------------|--------------------|
| POST   | `/companies`  | Create a company   |
| GET    | `/companies`  | List all companies |

### 💼 Jobs
| Method | Endpoint                        | Description                                 |
|--------|----------------------------------|---------------------------------------------|
| POST   | `/companies/{id}/jobs`          | Create job for a company                    |
| GET    | `/jobs`                         | List jobs with filters                      |
| GET    | `/jobs/{job_id}/applications`   | View candidates for a job (admin/recruiter) |
| POST   | `/jobs/{job_id}/apply`          | Apply to a job (user)                       |

</details>

---

## 🧪 Interactive API Docs (Swagger UI)

FastAPI provides a built-in interactive interface:

- 🔗 [Swagger UI](http://localhost:8000/docs)
- 🔗 [Redoc](http://localhost:8000/redoc)

You can test endpoints directly in your browser.

## 🧑‍💼 How to Test

1. ✅ Create a new user (preferably an **admin**)  
2. 🔐 Click the **"Authorize"** button in Swagger UI  
3. 👤 Enter just your `username` and `password` to log in  
4. 🟢 Now the entire API is unlocked and ready to use!

---

## 🔐 Authentication

All protected routes require an **access token** in the `Authorization` header:

```
Authorization: Bearer <access_token>
```

### ✅ Example Login (Terminal)
```bash
curl -X POST http://localhost:8000/auth/login \
     -H "Content-Type: application/x-www-form-urlencoded" \
     -d "username=youruser&password=yourpassword"
```

### ✅ Example Authenticated Request
```bash
curl -X GET http://localhost:8000/jobs \
     -H "Authorization: Bearer <access_token>"
```

---

## 📄 Endpoints

### 🔸 `POST /auth/register`
Registers a new user.

#### Request Body
```json
{
  "username": "string",
  "email": "user@example.com",
  "password": "string",
  "role": "user"
}
```

#### Response
Returns the created user object.

---

### 🔸 `POST /auth/login`
Authenticate user and return a JWT token.

#### Response
```json
{
  "access_token": "...",
  "token_type": "bearer"
}
```

---

### 🔹 `POST /companies`
Create a company (admin only).

#### Request Body
```json
{
  "name": "Test Company",
  "industry": "Tech",
  "size": "Small",
  "location": "Brazil",
  "website": "https://company.com",
  "description": "Test description"
}
```

---

### 🔹 `GET /companies`
List all companies.

---

### 🔹 `POST /companies/{company_id}/jobs`
Create a job posting (recruiter or admin).

#### Request Body
```json
{
  "title": "Backend Developer",
  "location": "Remote",
  "level": "Junior",
  "type": "Full-time",
  "requirements": ["Python", "FastAPI"],
  "deadline": "2025-12-31",
  "status": "open",
  "description": "Exciting role..."
}
```

---

### 🔹 `GET /jobs`
List all jobs. You can filter using query parameters:

```
/jobs?level=Junior&type=Full-time&location=Brazil
```

---

### 🔹 `POST /jobs/{job_id}/apply`
Apply for a job (user, recruiter, or admin).

---

### 🔹 `GET /users/me/applications`
List applications of the logged-in user.

---

### 🔹 `GET /jobs/{job_id}/applications`
List candidates who applied to a specific job (recruiter or admin).

---

